#ifndef AISD_TEST_HPP
#define AISD_TEST_HPP
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <graphlib>
#include <utility>
#include <vector>

namespace test {

    /*
        Example usage:

        const auto test_data = test::random_data({5, 20, 50}, {0.25, 0.5, 0.9}, 10);
        std::cout << "\n=== Adjacency matrix ===\n";
        test::run_test<gr::amatrix_dir_graph>(test_data);
        std::cout << "\n=== Incidence matrix ===\n";
        test::run_test<gr::imatrix_dir_graph>(test_data);
        std::cout << "\n=== Successors list ===\n";
        test::run_test<gr::slist_dir_graph>(test_data);
        std::cout << "\n=== Predecessors list ===\n";
        test::run_test<gr::plist_dir_graph>(test_data);
     */

    std::vector<std::tuple<int, float, std::vector<gr::amatrix_dir_graph>>>
    random_data(const std::vector<int>& vertices_numbers, const std::vector<float>& fill_degrees, int graphs_number) {
        std::vector<std::tuple<int, float, std::vector<gr::amatrix_dir_graph>>> test_data;
        for (int vertices_number : vertices_numbers) {
            for (float fill_degree : fill_degrees) {
                std::vector<gr::amatrix_dir_graph> single_test_data;
                for (int i = 0; i < graphs_number; i++)
                    single_test_data.push_back(gr::amatrix_dir_graph::random(vertices_number, fill_degree));
                test_data.emplace_back(vertices_number, fill_degree, single_test_data);
            }
        }
        return test_data;
    }

    template<typename Gr>
    requires std::is_base_of_v<gr::graph, Gr>
    void run_test(const std::vector<std::tuple<int, float, std::vector<gr::amatrix_dir_graph>>>& data) {

        gr::timer<gr::precision_us> timer;
        const std::string unit = timer.unit();

        for (const auto& test : data) {

            std::cout << "\n[ " << std::get<0>(test) << " vertices | " << std::get<1>(test) * 100 << "% fill ]\n";
            uint64_t bfs_time = 0, dfs_time = 0;

            const auto& graphs = std::get<2>(test);
            for (const auto& adjmatrix : graphs) {
                Gr graph = gr::intercom::convert<gr::amatrix_dir_graph, Gr>(adjmatrix);

                timer.start();
                gr::sort_bfs(graph);
                timer.stop();
                bfs_time += timer.get_measured_time();

                timer.start();
                gr::sort_dfs(graph);
                timer.stop();
                dfs_time += timer.get_measured_time();
            }

            std::cout << " -> BFS sorted in " << bfs_time << unit
                      << " (avg " << double(bfs_time) / double(graphs.size()) << unit << ")\n"
                      << " -> DFS sorted in " << dfs_time << unit
                      << " (avg " << double(dfs_time) / double(graphs.size()) << unit << ")\n";
        }
    }
}

#endif //AISD_TEST_HPP