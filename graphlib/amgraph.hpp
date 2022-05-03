#ifndef GRAPHLIB_AMGRAPH_HPP
#define GRAPHLIB_AMGRAPH_HPP

#include <algorithm>
#include <numeric>
#include <graph.hpp>
#include <util.hpp>

namespace gr {

    struct amatrix_dir_graph : graph {

        amatrix_dir_graph(const std::initializer_list<std::vector<int>>& init) : graph(init) {
            for (int i = 0; i < this->size_rows(); i++) header.push_back(i);
        }

        explicit amatrix_dir_graph(const std::vector<std::vector<int>>& vector) : graph(vector) {
            for (int i = 0; i < this->size_rows(); i++) header.push_back(i);
        }

        explicit amatrix_dir_graph(const gr::matrix<int>& matrix) : graph(matrix) {
            for (int i = 0; i < this->size_rows(); i++) header.push_back(i);
        }

        [[nodiscard]] int find_independent() const override {
            for (int vertex : header) {
                bool minus_one_found = false;
                int cell = 0;
                while (cell < (*this)[index_of(vertex)].size()) {
                    if ((*this)[index_of(vertex)][cell++] == -1) {
                        minus_one_found = true;
                        break;
                    }
                }
                if (not minus_one_found) return vertex;
            }
            return not_found;
        }

        [[nodiscard]] bool is_independent(int vertex) const override {
            const auto& row = (*this)[index_of(vertex)];
            return std::all_of(whole(row), [](int cell) { return cell != -1; });
        }

        void remove_vertex(int vertex) override {
            const size_t index = this->index_of(vertex);
            this->erase_column(index);
            this->erase_row(index);
            header.erase(header.begin() + int(index));
        }

        [[nodiscard]] std::vector<int> successors(int vertex) const override {
            std::vector<int> successors;
            const auto& row = (*this)[index_of(vertex)];
            for (int cell = 0; cell < row.size(); cell++) if (row[cell] == 1) successors.push_back(cell);
            return successors;
        }

        [[nodiscard]] std::vector<int> all_vertices() const override {
            return header;
        }
    };
}

#endif //GRAPHLIB_AMGRAPH_HPP
