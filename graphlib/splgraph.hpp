#pragma ide diagnostic ignored "bugprone-reserved-identifier"
#ifndef AISD_SPLGRAPH_HPP
#define AISD_SPLGRAPH_HPP

#include <amgraph.hpp>
#include <graph.hpp>

namespace gr {

    struct stateful_vertex {
        enum state {
            untouched, touched, sorted
        };
        int value;
        state state;
    };

    std::ostream& operator<<(std::ostream& out, const stateful_vertex& vertex) {
        return out << vertex.value << "("
                   << (vertex.state == 0 ? "untouched" : (vertex.state == 1 ? "touched" : "sorted")) << ")";
    }

    struct stateful_successors_list_dir_graph : graph<stateful_vertex> {

        stateful_successors_list_dir_graph(const std::initializer_list<std::vector<stateful_vertex>>& __init)
                : graph(__init) {}

        explicit stateful_successors_list_dir_graph(const std::vector<std::vector<stateful_vertex>>& __init)
                : graph(__init) {}

        [[nodiscard]] bool connected(stateful_vertex vertex1, stateful_vertex vertex2) const override {
            return false;
        }

        [[nodiscard]] std::vector<stateful_vertex> adjacent_nodes(stateful_vertex vertex) const override {
            return {};
        }

        [[nodiscard]] std::vector<std::pair<stateful_vertex, stateful_vertex>> all_edges() const override {
            return {};
        }
    };

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

        [[nodiscard]] stateful_successors_list_dir_graph stateful() {
            std::vector<std::vector<stateful_vertex>> vec;
            for (const auto& row : *this) {
                std::vector<stateful_vertex> new_row;
                for (const auto& cell : row) new_row.push_back({cell, stateful_vertex::state::untouched});
                vec.push_back(new_row);
            }
            return stateful_successors_list_dir_graph(vec);
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