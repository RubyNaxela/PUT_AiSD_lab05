#ifndef AISD_ELGRAPH_HPP
#define AISD_ELGRAPH_HPP

#include <graph.hpp>

namespace gr {

    struct edges_list_dir_graph : graph {

        edges_list_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {}

        [[nodiscard]] bool connected(int vertex1, int vertex2) const override {
            for (int i = 0; i < this->size_rows(); i++)
                if ((*this)[i][0] == vertex1 and (*this)[i][1] == vertex2) return true;
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

#endif //AISD_ELGRAPH_HPP
