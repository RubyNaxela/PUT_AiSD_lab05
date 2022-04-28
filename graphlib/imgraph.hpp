#ifndef AISD_IMGRAPH_HPP
#define AISD_IMGRAPH_HPP

#include <graph.hpp>

namespace gr {

    struct incidence_matrix_dir_graph : graph {

        incidence_matrix_dir_graph(const std::initializer_list<std::vector<int>>& __init) : graph(__init) {}

        [[nodiscard]] bool connected(int vertex1, int vertex2) const override {
            for (int i = 0; i < this->size_cols(); i++)
                if ((*this)[vertex1][i] == -1 and (*this)[vertex2][i] == 1) return true;
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

#endif //AISD_IMGRAPH_HPP
