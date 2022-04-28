#ifndef AISD_GRAPH_HPP
#define AISD_GRAPH_HPP

#include <initializer_list>
#include <utility>
#include <vector>
#include <boolstr.hpp>
#include <matrix.hpp>

namespace gr {

    struct graph : gr::matrix<int> {

        graph(const std::initializer_list<std::vector<int>>& __init) : gr::matrix<int>(__init) {}

        explicit graph(const std::vector<std::vector<int>>& __init) : gr::matrix<int>(__init) {}

        explicit graph(const gr::matrix<int>& __init) : gr::matrix<int>(__init) {}

        virtual ~graph() = default;

        ///
        /// \return whether this graph contains any vertices
        ///
        [[nodiscard]] bool empty() const {
            return this->size_rows() == 0;
        }

        ///
        /// \return whether there is an edge between vertices of the specified indices
        ///
        [[nodiscard]] virtual bool connected(int, int) const = 0;

        ///
        /// \return vector of indices of all vertices adjacent to the vertex of the specified index
        ///
        [[nodiscard]] virtual std::vector<int> adjacent_nodes(int) const = 0;

        ///
        /// \return all edges of this graph
        ///
        [[nodiscard]] virtual std::vector<std::pair<int, int>> all_edges() const = 0;
    };
}

#endif //AISD_GRAPH_HPP
