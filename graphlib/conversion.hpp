#ifndef GRAPHLIB_CONVERSION_HPP
#define GRAPHLIB_CONVERSION_HPP

#include <amgraph.hpp>
#include <imgraph.hpp>
#include <plgraph.hpp>
#include <slgraph.hpp>

namespace gr {

    class intercom {

        template<typename Origin>
        requires std::is_base_of_v<adjacency_matrix_dir_graph, Origin>
        static adjacency_matrix_dir_graph from_origin_to_adj_matrix(const Origin& graph) {
            return graph;
        }

        template<typename Target>
        requires std::is_base_of_v<adjacency_matrix_dir_graph, Target>
        static Target from_adj_matrix_to_target(const adjacency_matrix_dir_graph& graph) {
            return graph;
        }

        template<typename Target>
        requires std::is_base_of_v<predecessors_list_dir_graph, Target>
        static Target from_adj_matrix_to_target(const adjacency_matrix_dir_graph& graph) {
            std::vector<std::vector<int>> list_vec(graph.size_rows());
            for (int i = 0; i < graph.size_rows(); i++) {
                list_vec[i].push_back(i);
                for (int j = 0; j < graph.size_cols(); j++) if (graph[i][j] == -1) list_vec[i].push_back(j);
            }
            return predecessors_list_dir_graph(list_vec);
        }

        template<typename Target>
        requires std::is_base_of_v<successors_list_dir_graph, Target>
        static Target from_adj_matrix_to_target(const adjacency_matrix_dir_graph& graph) {
            std::vector<std::vector<int>> list_vec(graph.size_rows());
            for (int i = 0; i < graph.size_rows(); i++) {
                list_vec[i].push_back(i);
                for (int j = 0; j < graph.size_cols(); j++) if (graph[i][j] == 1) list_vec[i].push_back(j);
            }
            return successors_list_dir_graph(list_vec);
        }

        template<typename Target>
        requires std::is_base_of_v<incidence_matrix_dir_graph, Target>
        static Target from_adj_matrix_to_target(const adjacency_matrix_dir_graph& graph) {
            auto slist = from_adj_matrix_to_target<successors_list_dir_graph>(graph);
            incidence_matrix_dir_graph imdg(std::vector<std::vector<int>>(slist.size_rows()));
            auto add_edge = [&](int from, int to) {
                for (int i = 0; i < imdg.size_rows(); i++) {
                    auto& row = imdg[i];
                    if (i == from) row.push_back(-1);
                    else if (i == to) row.push_back(1);
                    else row.push_back(0);
                }
            };
            for (const auto& row : slist) {
                int origin = row[0];
                for (int i = 1; i < row.size(); i++) add_edge(origin, row[i]);
            }
            return imdg;
        }

    public:

        intercom() = delete;

        template<typename Origin, typename Target>
        requires std::is_base_of_v<graph, Origin> and std::is_base_of_v<graph, Target>
        static Target convert(const Origin& graph) {
            return from_adj_matrix_to_target<Target>(from_origin_to_adj_matrix<Origin>(graph));
        }
    };
}

#endif //GRAPHLIB_CONVERSION_HPP
