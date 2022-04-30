#pragma ide diagnostic ignored "bugprone-reserved-identifier"
#ifndef AISD_SPLGRAPH_HPP
#define AISD_SPLGRAPH_HPP

#include <map>
#include <numeric>
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
                for (int j = 0; j < matrix.size_cols(); j++) {
                    if (matrix[i][j] == 1) {
                        list_vec[i].push_back(j);
                    }
                }
            }
            return successors_list_dir_graph(list_vec);
        }

        [[nodiscard]] int find_independent() const override {
            std::set<int> successors;
            for (const auto& row : *this) for (int i = 1; i < row.size(); i++) successors.insert(row[i]);
            for (int vertex : this->all_vertices()) if (not successors.contains(vertex)) return vertex;
            return -1;
        }

        [[nodiscard]] bool is_independent(int vertex) const override {
            for (const auto& row : *this)
                if (std::any_of(row.begin() + 1, row.end(), [=](int v) { return v == vertex; })) return false;
            return true;
        }

        void remove_vertex(int vertex) override {
            for (auto row = this->begin(); row != this->end(); row++) {
                if ((*row)[0] == vertex) {
                    this->erase_row(row--);
                    continue;
                }
                std::erase_if(*row, [&](int x) { return x == vertex; });
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

    struct predecessors_list_dir_graph : graph {

        predecessors_list_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {}

        explicit predecessors_list_dir_graph(const std::vector<std::vector<int>>& __init) : graph(__init) {}

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

        [[nodiscard]] int find_independent() const override {
            return (*std::find_if(whole(*this), [&](const auto& row) { return row.size() == 1; }))[0];
        }

        [[nodiscard]] bool is_independent(int vertex) const override {
            return (*this)[vertex].size() == 1;
        }

        void remove_vertex(int vertex) override {
            for (auto row = this->begin(); row != this->end(); row++) {
                if ((*row)[0] == vertex) {
                    this->erase_row(row--);
                    continue;
                }
                std::erase_if(*row, [&](int x) { return x == vertex; });
            }
        }

        [[nodiscard]] std::vector<int> successors(int vertex) const override {
            std::vector<int> successors;
            for (const auto& row : *this)
                if (row[0] != vertex and std::count(whole(row), vertex) > 0) successors.push_back(row[0]);
            return successors;
        }

        [[nodiscard]] std::vector<int> all_vertices() const override {
            std::vector<int> vertices;
            for (const auto& row : *this) vertices.push_back(row[0]);
            return vertices;
        }
    };
}

#endif //AISD_SPLGRAPH_HPP