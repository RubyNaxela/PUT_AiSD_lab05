#ifndef AISD_GMGRAPH_HPP
#define AISD_GMGRAPH_HPP

#include <graph.hpp>
#include <util.hpp>

namespace gr {

    struct graph_matrix_dir_graph : graph {

        graph_matrix_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {}

        explicit graph_matrix_dir_graph(const std::vector<std::vector<int>>& __init) : graph(__init) {}

        static graph_matrix_dir_graph from_adjacency_matrix(const adjacency_matrix_dir_graph& matrix) {
            std::vector<std::vector<int>> successors_list(matrix.size_rows());
            std::vector<std::vector<int>> predecessors_list(matrix.size_rows());
            std::vector<std::vector<int>> no_incidence_list(matrix.size_rows());
            for (int i = 0; i < matrix.size_rows(); i++) {
                successors_list[i].push_back(i);
                for (int j = 0; j < matrix.size_cols(); j++) {
                    if (matrix[i][j] == 1) {
                        successors_list[i].push_back(j);
                    }
                }
            }
            for (int i = 0; i < matrix.size_rows(); i++) {
                predecessors_list[i].push_back(i);
                for (int j = 0; j < matrix.size_cols(); j++) {
                    if (matrix[i][j] == -1) {
                        predecessors_list[i].push_back(j);
                    }
                }
            }
            for (int i = 0; i < matrix.size_rows(); i++) {
                no_incidence_list[i].push_back(i);
                for (int j = 0; j < matrix.size_cols(); j++) {
                    if (matrix[i][j] == 0) {
                        no_incidence_list[i].push_back(j);
                    }
                }
            }
            std::vector<std::vector<int>> graph_matrix;



            return graph_matrix_dir_graph(graph_matrix);
        }

        [[nodiscard]] int find_independent() const override {
            return not_found;
        }

        [[nodiscard]] bool is_independent(int vertex) const override {
            return true;
        }

        void remove_vertex(int vertex) override {

        }

        [[nodiscard]] std::vector<int> successors(int vertex) const override {
            return {};
        }

        [[nodiscard]] std::vector<int> all_vertices() const override {
            return {};
        }
    };
}

#endif //AISD_GMGRAPH_HPP
