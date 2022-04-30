#ifndef AISD_GRAPH_HPP
#define AISD_GRAPH_HPP

#include <initializer_list>
#include <utility>
#include <vector>
#include <matrix.hpp>

namespace gr {

    ///
    /// \brief The base class for all graph representations. Requires that the number of rows
    /// of the underlying matrix is equal to the number of vertices of the graph being represented.
    /// The indices of these rows do not need to be identical to the indices of the graph vertices.
    ///
    struct graph : gr::matrix<int> {

        graph(const std::initializer_list<std::vector<int>>& init) : gr::matrix<int>(init) {}

        explicit graph(const std::vector<std::vector<int>>& vec) : gr::matrix<int>(vec) {}

        explicit graph(const gr::matrix<int>& matrix) : gr::matrix<int>(matrix) {}

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
        /// \return whether the specified vertex has no predecessors
        ///
        [[nodiscard]] virtual bool is_independent(int) const = 0;

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
