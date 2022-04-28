#ifndef AISD_GMGRAPH_HPP
#define AISD_GMGRAPH_HPP

#include <graph.hpp>

namespace gr {

    struct graph_matrix_dir_graph : int_graph {

        graph_matrix_dir_graph(const std::initializer_list<std::vector<int>>& __init) : int_graph(__init) {}

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

#endif //AISD_GMGRAPH_HPP
