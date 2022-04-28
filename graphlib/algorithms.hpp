#ifndef AISD_ALGORITHMS_HPP
#define AISD_ALGORITHMS_HPP

#include <map>
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
        std::map<int, vertex_state> states;
        std::vector<int> vertices;

        return vertices;
    }
}

#endif //AISD_ALGORITHMS_HPP
