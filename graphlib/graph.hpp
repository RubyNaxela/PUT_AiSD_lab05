#ifndef AISD_GRAPH_HPP
#define AISD_GRAPH_HPP

#include <initializer_list>
#include <utility>
#include <vector>
#include <boolstr.hpp>
#include <matrix.hpp>

namespace gr {

    template<typename _Tp>
    struct graph : gr::matrix<_Tp> {

        graph(const std::initializer_list<std::vector<_Tp>>& __init) : gr::matrix<_Tp>(__init) {}

        explicit graph(const std::vector<std::vector<_Tp>>& __init) : gr::matrix<_Tp>(__init) {}

        explicit graph(const gr::matrix<_Tp>& __init) : gr::matrix<_Tp>(__init) {}

        virtual ~graph() = default;

        ///
        /// \return whether there is an edge between vertices of the specified indices
        ///
        [[nodiscard]] virtual bool connected(_Tp, _Tp) const = 0;

        ///
        /// \return vector of indices of all vertices adjacent to the vertex of the specified index
        ///
        [[nodiscard]] virtual std::vector<_Tp> adjacent_nodes(_Tp) const = 0;

        ///
        /// \return all edges of the inc
        ///
        [[nodiscard]] virtual std::vector<std::pair<_Tp, _Tp>> all_edges() const = 0;
    };

    typedef graph<int> int_graph;
}

#endif //AISD_GRAPH_HPP
