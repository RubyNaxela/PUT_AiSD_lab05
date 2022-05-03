#ifndef GRAPHLIB_GMGRAPH_HPP
#define GRAPHLIB_GMGRAPH_HPP

#include <stdexcept>
#include <graph.hpp>
#include <util.hpp>

namespace gr {

    class gmatrix_dir_graph : public graph {

        int max_vertex = 0;

        [[nodiscard]] bool predecessor_range(int cell) const {
            return cell > max_vertex + 1 and cell <= 2 * (max_vertex + 1);
        }

        [[nodiscard]] bool no_incidence_range(int cell) const {
            return cell < 0 and cell >= -max_vertex - 1;
        }

        [[nodiscard]] bool successor_range(int cell) const {
            return cell > 0 and cell <= max_vertex + 1;
        }

    public:

        gmatrix_dir_graph(const std::initializer_list<std::vector<int>>& init) : graph(init) {
            for (int i = 0; i < this->size_rows(); i++) header.push_back(i);
            max_vertex = int(this->size_rows() - 1);
        }

        explicit gmatrix_dir_graph(const std::vector<std::vector<int>>& vec) : graph(vec) {
            for (int i = 0; i < this->size_rows(); i++) header.push_back(i);
            max_vertex = int(this->size_rows() - 1);
        }

        static gmatrix_dir_graph from_amatrix(const amatrix_dir_graph& graph) {
            std::vector<std::vector<int>> successors_list(graph.size_rows()),
                    predecessors_list(graph.size_rows()),
                    no_incidence_list(graph.size_rows());
            for (int i = 0; i < graph.size_rows(); i++) {
                successors_list[i].push_back(i);
                predecessors_list[i].push_back(i);
                no_incidence_list[i].push_back(i);
                for (int j = 0; j < graph.size_cols(); j++) {
                    if (graph[i][j] == 1) successors_list[i].push_back(j);
                    else if (graph[i][j] == -1) predecessors_list[i].push_back(j);
                    else no_incidence_list[i].push_back(j);
                }
            }
            const size_t graph_size = graph.size_rows();
            std::vector<std::vector<int>> graph_matrix(graph_size);
            for (auto& row : graph_matrix) row = std::vector<int>(graph_size + 3);
            auto fill_list = [&](const auto& list, size_t column, auto transform) {
                auto row = graph_matrix.begin();
                for (const auto& list_row : list) {
                    if (list_row.size() > 1) (*row)[column] = list_row[1] + 1;
                    else (*row)[column] = 0;
                    for (int cell = 1; cell < list_row.size(); cell++)
                        (*row)[list_row[cell]] = transform(list_row[list_row.size() - 1]);
                    row++;
                }
            };
            fill_list(successors_list, graph_size, [](int c) { return c + 1; });
            fill_list(predecessors_list, graph_size + 1, [=](int c) { return c + 1 + graph_size; });
            fill_list(no_incidence_list, graph_size + 2, [](int c) { return -c - 1; });
            auto gmatrix = gmatrix_dir_graph(graph_matrix);
            gmatrix.set_header_from(graph);
            return gmatrix;
        }

        [[nodiscard]] amatrix_dir_graph to_amatrix() const {
            std::vector<std::vector<int>> vec(this->size_rows());
            auto vec_row = vec.begin();
            for (const auto& row : *this) {
                for (auto cell = row.begin(); cell != row.begin() + int64_t(this->size_rows()); cell++) {
                    if (predecessor_range(*cell)) vec_row->push_back(-1);
                    else if (successor_range(*cell)) vec_row->push_back(1);
                    else vec_row->push_back(0);
                }
                vec_row++;
            }
            auto amatrix = amatrix_dir_graph(vec);
            amatrix.set_header_from(*this);
            return amatrix;
        }

        [[nodiscard]] int find_independent() const override {
            for (int vertex : header) {
                bool predecessor_range_found = false;
                int cell = 0;
                while (cell < this->size_rows()) {
                    if (predecessor_range((*this)[index_of(vertex)][cell++])) {
                        predecessor_range_found = true;
                        break;
                    }
                }
                if (not predecessor_range_found) return vertex;
            }
            return not_found;
        }

        [[nodiscard]] bool is_independent(int vertex) const override {
            const auto& row = (*this)[index_of(vertex)];
            return std::all_of(row.begin(), row.begin() + int64_t(this->size_rows()),
                               [&](int cell) { return no_incidence_range(cell) or successor_range(cell); });
        }

        void remove_vertex(int vertex) override {
            auto amatrix = this->to_amatrix();
            amatrix.remove_vertex(vertex);
            *this = from_amatrix(amatrix);
        }

        [[nodiscard]] std::vector<int> successors(int vertex) const override {
            std::vector<int> successors;
            const auto& row = (*this)[index_of(vertex)];
            for (int cell = 0; cell < this->size_rows(); cell++)
                if (successor_range(row[cell])) successors.push_back(cell);
            return successors;
        }

        [[nodiscard]] std::vector<int> all_vertices() const override {
            return header;
        }
    };
}

#endif //GRAPHLIB_GMGRAPH_HPP
