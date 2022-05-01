#ifndef GRAPHLIB_ELGRAPH_HPP
#define GRAPHLIB_ELGRAPH_HPP

#include <graph.hpp>
#include <util.hpp>

namespace gr {

    struct edges_list_dir_graph : graph {

        edges_list_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {}

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

#endif //GRAPHLIB_ELGRAPH_HPP
