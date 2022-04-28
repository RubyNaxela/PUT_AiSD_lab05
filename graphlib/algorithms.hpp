#ifndef AISD_ALGORITHMS_HPP
#define AISD_ALGORITHMS_HPP
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "UnusedLocalVariable"
#pragma ide diagnostic ignored "UnusedParameter"

#include <map>
#include <stack>
#include <vector>
#include <amgraph.hpp>
#include <splgraph.hpp>
#include <util.hpp>

namespace gr {

    enum vertex_state {
        untouched = *"untouched", touched = *"touched", sorted = *"sorted"
    };

    template<typename Gr>
    requires std::is_base_of_v<graph, Gr>
    std::vector<int> sort_bfs(const Gr& __graph) {
        Gr graph = __graph;
        std::vector<int> vertices;
        while (not graph.empty()) {
            const int independent = graph.find_independent();
            vertices.push_back(independent);
            graph.remove_vertex(independent);
        }
        return vertices;
    }

    template<typename Gr>
    requires std::is_base_of_v<graph, Gr>
    std::vector<int> sort_dfs(const Gr& __graph) {

        Gr graph = __graph;
        std::map<int, vertex_state> states;
        std::stack<int> path;

        auto white_successor = [&](int vertex) -> int {
            for (int v: graph.successors(vertex)) if (states[v] == vertex_state::untouched) return v;
            return -1;
        };

        auto any_white = [&]() -> bool {
            for (int v: graph.all_vertices()) if (states[v] == vertex_state::untouched) return true;
            return false;
        };

        for (int vertex: graph.all_vertices()) states[vertex] = vertex_state::untouched;
        std::vector<int> vertices;

        step_4:
        int u = graph.find_independent();
        if (states[u] != vertex_state::untouched) {
            u = *std::find_if(scan(graph.all_vertices()), [&](int v) { return states[v] == vertex_state::untouched; });
        }

        step_5:
        path.push(u);
        states[u] = vertex_state::touched;

        step_6:
        int u_successor = white_successor(u);
        if (u_successor != -1) {
            u = u_successor;
            goto step_5;
        } else {
            states[u] = vertex_state::sorted;
            vertices.insert(vertices.begin(), u);
        }

        path.pop();
        if (not path.empty()) {
            u = path.top();
            goto step_6;
        } else {
            if (vertices.size() == graph.all_vertices().size()) goto step_11;
            if (any_white()) goto step_4;
        }
        step_11:
        return vertices;
    }
}

#endif //AISD_ALGORITHMS_HPP
