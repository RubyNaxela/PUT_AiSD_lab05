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
        /// \return the first independent vertex of this graph
        ///
        [[nodiscard]] virtual int find_independent() const = 0;

        ///
        /// \brief Removes the specified vertex from this graph.
        ///
        virtual void remove_vertex(int) = 0;

        ///
        /// \return vector of all successors of the specified vertex
        ///
        [[nodiscard]] virtual std::vector<int> successors(int) const = 0;

        ///
        /// \return all vertices of this graph
        ///
        [[nodiscard]] virtual std::vector<int> all_vertices() const = 0;
    };
}

#endif //AISD_GRAPH_HPP
