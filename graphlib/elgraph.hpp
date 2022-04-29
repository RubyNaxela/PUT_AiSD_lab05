#ifndef AISD_ELGRAPH_HPP
#define AISD_ELGRAPH_HPP

#include <graph.hpp>

namespace gr {

    struct edges_list_dir_graph : graph {

        edges_list_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {}

        [[nodiscard]] std::vector<int> successors(int vertex) const override {
            return {};
        }

        [[nodiscard]] std::vector<int> all_vertices() const override {
            return {};
        }
    };
}

#endif //AISD_ELGRAPH_HPP
