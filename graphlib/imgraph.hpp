#ifndef AISD_IMGRAPH_HPP
#define AISD_IMGRAPH_HPP

#include <graph.hpp>
#include <splgraph.hpp>
#include <util.hpp>

namespace gr {

    struct incidence_matrix_dir_graph : graph {

    private:

        std::vector<int> header;

        [[nodiscard]] int index_of(int vertex) const {
            return int(std::find(whole(header), vertex) - header.begin());
        }

        void add_edge(int from, int to) {
            for (int i = 0; i < this->size_rows(); i++) {
                auto& row = (*this)[i];
                if (i == from) row.push_back(-1);
                else if (i == to) row.push_back(1);
                else row.push_back(0);
            }
        }

    public:

        incidence_matrix_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {
            for (int i = 0; i < this->size_rows(); i++) header.push_back(i);
        }

        explicit incidence_matrix_dir_graph(const std::vector<std::vector<int>>& __init) : graph(__init) {
            for (int i = 0; i < this->size_rows(); i++) header.push_back(i);
        }

        static incidence_matrix_dir_graph from_adjacency_matrix(const adjacency_matrix_dir_graph& matrix) {
            auto slist = gr::successors_list_dir_graph::from_adjacency_matrix(matrix);
            incidence_matrix_dir_graph imdg(std::vector<std::vector<int>>(slist.size_rows()));
            for (const auto& row : slist) {
                int origin = row[0];
                for (int i = 1; i < row.size(); i++) imdg.add_edge(origin, row[i]);
            }
            return imdg;
        }

        [[nodiscard]] int find_independent() const override {
            if (this->size_cols() == 0) return header[0];
            for (int row = 0; row < this->size_rows(); row++) {
                bool one_found = false;
                int cell = 0;
                for (; cell < (*this)[row].size(); cell++) {
                    if ((*this)[row][cell] == 1) {
                        one_found = true;
                        break;
                    }
                }
                if (not one_found) return header[row];
            }
            return not_found;
        }

        [[nodiscard]] bool is_independent(int vertex) const override {
            const auto& row = (*this)[index_of(vertex)];
            return std::all_of(whole(row), [](int cell) { return cell != 1; });
        }

        void remove_vertex(int vertex) override {
            const int index = this->index_of(vertex);
            auto& row = (*this)[index];
            for (int i = 0; i < row.size(); i++) if (row[i] != 0) this->erase_column(i--);
            if (index < this->size_rows()) {
                this->erase_row(index);
                header.erase(header.begin() + int(index));
            }
        }

        [[nodiscard]] std::vector<int> successors(int vertex) const override {
            std::vector<int> successors;
            const auto& vertex_row = (*this)[vertex];
            for (int col = 0; col < vertex_row.size(); col++)
                if (vertex_row[col] == -1)
                    for (int row = 0; row < this->size_rows(); row++)
                        if ((*this)[row][col] == 1) successors.push_back(row);
            return successors;
        }

        [[nodiscard]] std::vector<int> all_vertices() const override {
            return header;
        }
    };
}

#endif //AISD_IMGRAPH_HPP
