#ifndef GRAPHLIB_GRAPH_HPP
#define GRAPHLIB_GRAPH_HPP

#include <initializer_list>
#include <utility>
#include <vector>
#include <matrix.hpp>
#include <util.hpp>

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

        ///
        /// \brief Transfers the header from the specified graph to this graph.
        /// \param graph the graph to transfer the header from
        ///
        template<typename Gr>
        requires std::is_base_of_v<graph, Gr>
        void set_header_from(const Gr& graph) {
            this->header = graph.header;
        }

    protected:

        ///
        /// \brief Used by matrix representations as a list of graph vertex indices, since those
        /// (unlike list representations) do not themselves contain information about the indices.
        ///
        std::vector<int> header;

        ///
        /// \brief Returns which row of the matrix representation contains data for
        /// the vertex with the specified index. Used only by matrix representations.
        /// \return position of the specified vertex in the header
        ///
        [[nodiscard]] int index_of(int vertex) const {
            return int(std::find(whole(header), vertex) - header.begin());
        }
    };
}

#endif //GRAPHLIB_GRAPH_HPP
