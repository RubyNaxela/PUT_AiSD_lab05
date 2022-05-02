#ifndef GRAPHLIB_PLGRAPH_HPP
#define GRAPHLIB_PLGRAPH_HPP

#include <amgraph.hpp>
#include <graph.hpp>
#include <util.hpp>

namespace gr {

    struct predecessors_list_dir_graph : graph {

        predecessors_list_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {}

        explicit predecessors_list_dir_graph(const std::vector<std::vector<int>>& __init) : graph(__init) {}

        [[nodiscard]] int find_independent() const override {
            const auto row = std::find_if(whole(*this), [&](const auto& r) { return r.size() == 1; });
            return row != this->end() ? (*row)[0] : not_found;
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
                std::erase(*row, vertex);
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

#endif //GRAPHLIB_PLGRAPH_HPP
