#ifndef AISD_ALGORITHMS_HPP
#define AISD_ALGORITHMS_HPP

#include <vector>
#include <amgraph.hpp>
#include <splgraph.hpp>

namespace gr {

    std::vector<int> sort_bfs(const adjacency_matrix_dir_graph& matrix) {
        auto plist = gr::predecessors_list_dir_graph::from_adjacency_matrix(matrix);
        std::vector<int> vertices;
        while (plist.size_rows() > 0) {
            int independent;
            for (auto row = plist.begin(); row != plist.end(); row++) {
                if (row->size() == 1) {
                    independent = (*row)[0];
                    vertices.push_back(independent);
                    plist.erase_row(row--);
                    for (auto& _row : plist) std::erase_if(_row, [&](int x) { return x == independent; });
                }
            }
        }
        return vertices;
    }

    std::vector<int> sort_dfs(const adjacency_matrix_dir_graph& matrix) {

        auto plist = gr::predecessors_list_dir_graph::from_adjacency_matrix(matrix);
        auto slist = gr::successors_list_dir_graph::from_adjacency_matrix(matrix).stateful();

        std::cout << "SORTINK WITH DFS\n" << slist << std::endl;

        return {};
    }
}

#endif //AISD_ALGORITHMS_HPP
