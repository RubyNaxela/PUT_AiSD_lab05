#pragma ide diagnostic ignored "bugprone-reserved-identifier"
#ifndef AISD_SPLGRAPH_HPP
#define AISD_SPLGRAPH_HPP

#include <amgraph.hpp>
#include <graph.hpp>

namespace gr {

    template<typename _Tp>
    std::string vec_str(const std::vector<_Tp>& __vec) {
        std::stringstream ss;
        for (const auto& x : __vec) ss << x << " ";
        return ss.str();
    }

    template<typename _Tp>
    bool contains_any(const std::vector<_Tp>& vec1, const std::vector<_Tp>& vec2) {
        for (const auto& x : vec1) for (const auto& y : vec2) if (x == y) return true;
        return false;
    }

    struct successors_list_dir_graph : int_graph {

        successors_list_dir_graph(const std::initializer_list<std::vector<int>>& __init) : int_graph(__init) {}

        explicit successors_list_dir_graph(const std::vector<std::vector<int>>& __init) : int_graph(__init) {}

        static successors_list_dir_graph from_adjacency_matrix(const adjacency_matrix_dir_graph& matrix) {
            std::vector<std::vector<int>> list_vec(matrix.size_rows());
            for (int i = 0; i < matrix.size_rows(); i++) {
                list_vec[i].push_back(i);
                for (int j = 0; j < matrix.size_cols(); j++) {
                    if (matrix[i][j] == 1) {
                        list_vec[i].push_back(j);
                    }
                }
            }
            return successors_list_dir_graph(list_vec);
        }

        [[nodiscard]] bool connected(int vertex1, int vertex2) const override {
            return false;
        }

        [[nodiscard]] std::vector<int> adjacent_nodes(int vertex) const override {
            return {};
        }

        [[nodiscard]] std::vector<std::pair<int, int>> all_edges() const override {
            return {};
        }
    };

    struct predecessors_list_dir_graph : int_graph {

        predecessors_list_dir_graph(const std::initializer_list<std::vector<int>>& __init) : int_graph(__init) {}

        explicit predecessors_list_dir_graph(const std::vector<std::vector<int>>& __init) : int_graph(__init) {}

        static predecessors_list_dir_graph from_adjacency_matrix(const adjacency_matrix_dir_graph& matrix) {
            std::vector<std::vector<int>> list_vec(matrix.size_rows());
            for (int i = 0; i < matrix.size_rows(); i++) {
                list_vec[i].push_back(i);
                for (int j = 0; j < matrix.size_cols(); j++) {
                    if (matrix[i][j] == -1) {
                        list_vec[i].push_back(j);
                    }
                }
            }
            return predecessors_list_dir_graph(list_vec);
        }

        [[nodiscard]] bool connected(int vertex1, int vertex2) const override {
            return false;
        }

        [[nodiscard]] std::vector<int> adjacent_nodes(int vertex) const override {
            return {};
        }

        [[nodiscard]] std::vector<std::pair<int, int>> all_edges() const override {
            return {};
        }
    };
}

#endif //AISD_SPLGRAPH_HPP