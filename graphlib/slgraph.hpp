#ifndef GRAPHLIB_SLGRAPH_HPP
#define GRAPHLIB_SLGRAPH_HPP

#include <set>
#include <amgraph.hpp>
#include <graph.hpp>
#include <util.hpp>

namespace gr {

    struct successors_list_dir_graph : graph {

        successors_list_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {}

        explicit successors_list_dir_graph(const std::vector<std::vector<int>>& __init) : graph(__init) {}

        static successors_list_dir_graph from_adjacency_matrix(const adjacency_matrix_dir_graph& matrix) {
            std::vector<std::vector<int>> list_vec(matrix.size_rows());
            for (int i = 0; i < matrix.size_rows(); i++) {
                list_vec[i].push_back(i);
                for (int j = 0; j < matrix.size_cols(); j++) if (matrix[i][j] == 1) list_vec[i].push_back(j);
            }
            return successors_list_dir_graph(list_vec);
        }

        [[nodiscard]] int find_independent() const override {
            std::set<int> successors;
            for (const auto& row : *this) for (int i = 1; i < row.size(); i++) successors.insert(row[i]);
            for (int vertex : this->all_vertices()) if (not successors.contains(vertex)) return vertex;
            return not_found;
        }

        [[nodiscard]] bool is_independent(int vertex) const override {
            return std::none_of(whole(*this),
                                [=](const auto& row) { return std::count(row.begin() + 1, row.end(), vertex); });
        }

        void remove_vertex(int vertex) override {
            for (auto row = this->begin(); row != this->end(); row++) {
                if ((*row)[0] == vertex) {
                    this->erase_row(row--);
                    continue;
                }
                std::erase(*row, vertex);
            }
        }

        [[nodiscard]] std::vector<int> successors(int vertex) const override {
            std::vector<int> successors;
            const std::vector<int>& row = (*this)[vertex];
            for (int i = 1; i < row.size(); i++) successors.push_back(row[i]);
            return successors;
        }

        [[nodiscard]] std::vector<int> all_vertices() const override {
            std::vector<int> vertices;
            for (const auto& row : *this) vertices.push_back(row[0]);
            return vertices;
        }
    };
}

#endif //GRAPHLIB_SLGRAPH_HPP
