#ifndef AISD_ALGORITHMS_HPP
#define AISD_ALGORITHMS_HPP
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "UnusedParameter"

#include <map>
#include <stack>
#include <stdexcept>
#include <vector>
#include <amgraph.hpp>
#include <splgraph.hpp>
#include <util.hpp>

namespace gr {

    struct graph_error : std::runtime_error {
        explicit graph_error(const std::string& message) : runtime_error(message) {}
    };

    template<typename Gr>
    requires std::is_base_of_v<graph, Gr>
    std::vector<int> sort_bfs(const Gr& __graph) {
        Gr graph = __graph;
        std::vector<int> vertices;
        while (not graph.empty()) {
            const int independent = graph.find_independent();
            if (independent is_not_found) throw graph_error("Graph is not acyclic");
            vertices.push_back(independent);
            graph.remove_vertex(independent);
        }
        return vertices;
    }

    template<typename Gr>
    requires std::is_base_of_v<graph, Gr>
    class dfs_traversor {

        enum vertex_state {
            untouched, touched, sorted
        };

        const Gr& graph;
        std::map<int, vertex_state> states;
        std::stack<int> path;

    public:

        explicit dfs_traversor(const Gr& source) : graph(source) {
            for (int vertex : graph.all_vertices()) states[vertex] = vertex_state::untouched;
        }

        [[nodiscard]] int find_white() const {
            const int vertex = graph.find_independent();
            if (states.at(vertex) == vertex_state::untouched) return vertex;
            const auto all_vertices = graph.all_vertices();
            return *std::find_if(whole(all_vertices), [&](int v) {
                return graph.is_independent(v) and states.at(v) == vertex_state::untouched;
            });
        };

        void visit(int vertex) {
            path.push(vertex);
            states[vertex] = vertex_state::touched;
        }

        [[nodiscard]] int current_vertex() const {
            return path.top();
        }

        [[nodiscard]] int white_successor() const {
            for (int v : graph.successors(current_vertex())) if (states.at(v) == vertex_state::untouched) return v;
            return not_found;
        };

        [[nodiscard]] bool can_advance() const {
            return white_successor() is_found;
        }

        void mark_sorted() {
            states[current_vertex()] = vertex_state::sorted;
        }

        void go_back() {
            path.pop();
        }

        [[nodiscard]] bool path_empty() const {
            return path.empty();
        }

        [[nodiscard]] bool any_white() const {
            const auto& vertices = graph.all_vertices();
            return std::any_of(whole(vertices), [&](int v) { return states.at(v) == vertex_state::untouched; });
        };
    };

    template<typename Gr>
    requires std::is_base_of_v<graph, Gr>
    std::vector<int> sort_dfs(const Gr& graph) {
        dfs_traversor<Gr> dfs_graph(graph);
        std::vector<int> vertices;
        do {
            dfs_graph.visit(dfs_graph.find_white());
            do {
                if (not dfs_graph.can_advance()) {
                    dfs_graph.mark_sorted();
                    vertices.insert(vertices.begin(), dfs_graph.current_vertex());
                    dfs_graph.go_back();
                    continue;
                }
                dfs_graph.visit(dfs_graph.white_successor());
            } while (not dfs_graph.path_empty());
        } while (dfs_graph.any_white());
        return vertices;
    }
}

#endif //AISD_ALGORITHMS_HPP
