#ifndef AISD_AMGRAPH_HPP
#define AISD_AMGRAPH_HPP

#include <algorithm>
#include <numeric>
#include <graph.hpp>
#include <random.hpp>

namespace gr {

    struct adjacency_matrix_graph : int_graph {

        adjacency_matrix_graph(const std::initializer_list<std::vector<int>>& __init) : int_graph(__init) {}

        [[nodiscard]] bool connected(int vertex1, int vertex2) const override {
            return (*this)[vertex1][vertex2] == 1;
        }

        [[nodiscard]] std::vector<int> adjacent_nodes(int vertex) const override {
            return {};
        }

        [[nodiscard]] std::vector<std::pair<int, int>> all_edges() const override {
            return {};
        }
    };

    struct adjacency_matrix_dir_graph : int_graph {

        adjacency_matrix_dir_graph(const std::initializer_list<std::vector<int>>& __init) : int_graph(__init) {}

        explicit adjacency_matrix_dir_graph(const gr::matrix<int>& __init) : int_graph(__init) {}

        ///
        /// \brief Creates a random adjacency matrix representation of a directed graph.
        /// \param vertices the number of vertices in the graph
        /// \param fill the degree of fill
        /// \return
        ///
        static adjacency_matrix_dir_graph random(int vertices, float fill) {
            std::vector<std::vector<int>> vec(vertices);
            for (int i = 0; i < vertices; ++i) {
                for (int j = i; j < vertices; ++j) {
                    if (i == j) {
                        vec[i].push_back(0);
                    } else if (j > i) {
                        int r = gr::random_bool(fill);
                        vec[i].push_back(r);
                        vec[j].push_back(r == 1 ? -1 : 0);
                    }
                }
            }
            std::vector<int> shuffled_indices(vertices);
            std::iota(shuffled_indices.begin(), shuffled_indices.end(), 0);
            std::shuffle(shuffled_indices.begin(), shuffled_indices.end(), gr::random::engine);
            gr::matrix<int> matrix(vertices, vertices);
            int r = 0;
            for (int row_index : shuffled_indices) {
                int c = 0;
                for (int col_index : shuffled_indices) matrix[r][c++] = vec[row_index][col_index];
                r++;
            }
            return adjacency_matrix_dir_graph(matrix);
        }

        [[nodiscard]] bool connected(int vertex1, int vertex2) const override {
            return (*this)[vertex1][vertex2] == 1;
        }

        [[nodiscard]] std::vector<int> adjacent_nodes(int vertex) const override {
            return {};
        }

        [[nodiscard]] std::vector<std::pair<int, int>> all_edges() const override {
            return {};
        }
    };
}

#endif //AISD_AMGRAPH_HPP
