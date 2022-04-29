#ifndef AISD_AMGRAPH_HPP
#define AISD_AMGRAPH_HPP

#include <algorithm>
#include <numeric>
#include <graph.hpp>
#include <random.hpp>
#include <util.hpp>

namespace gr {

    struct adjacency_matrix_dir_graph : graph {

    private:

        std::vector<int> header;

        [[nodiscard]] int index_of(int vertex) const {
            return int(std::find(scan(header), vertex) - header.begin());
        }

    public:

        adjacency_matrix_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {
            for (int i = 0; i < this->size_rows(); i++) header.push_back(i);
        }

        explicit adjacency_matrix_dir_graph(const gr::matrix<int>& __init) : graph(__init) {
            for (int i = 0; i < this->size_rows(); i++) header.push_back(i);
        }

        ///
        /// \brief Creates a random adjacency matrix representation of a directed acyclic graph.
        /// \param vertices the number of vertices in the graph
        /// \param fill the degree of fill
        /// \return a random DAG adjacency matrix
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

        [[nodiscard]] int find_independent() const override {
            for (int row : header) {
                bool minus_one_found = false;
                int cell = 0;
                while (cell < (*this)[index_of(row)].size()) {
                    if ((*this)[index_of(row)][cell++] == -1) {
                        minus_one_found = true;
                        break;
                    }
                }
                if (not minus_one_found)
                    return row;
            }
            return -1;
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

#endif //AISD_AMGRAPH_HPP
