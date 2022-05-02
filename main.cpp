#include <graphlib>

int main() {

    const gr::amatrix_dir_graph adjm = {{0,  1,  0,  0,  0, 0, 0,  0},
                                        {-1, 0,  1,  1,  1, 0, 0,  0},
                                        {0,  -1, 0,  1,  0, 1, 0,  0},
                                        {0,  -1, -1, 0,  0, 1, -1, 0},
                                        {0,  -1, 0,  0,  0, 0, 0,  0},
                                        {0,  0,  -1, -1, 0, 0, 0,  -1},
                                        {0,  0,  0,  1,  0, 0, 0,  -1},
                                        {0,  0,  0,  0,  0, 1, 1,  0}};
    const auto incm = gr::intercom::convert<gr::amatrix_dir_graph, gr::imatrix_dir_graph>(adjm);
    const auto plist = gr::intercom::convert<gr::amatrix_dir_graph, gr::plist_dir_graph>(adjm);
    const auto slist = gr::intercom::convert<gr::amatrix_dir_graph, gr::slist_dir_graph>(adjm);

    std::cout << adjm << std::endl;
    std::cout << incm << std::endl;
    std::cout << plist << std::endl;
    std::cout << slist << std::endl;

    std::cout << "\nSORTED WITH BFS: " << gr::sort_bfs(adjm) << "\n";
    std::cout << "SORTED WITH BFS: " << gr::sort_bfs(incm) << "\n";
    std::cout << "SORTED WITH BFS: " << gr::sort_bfs(plist) << "\n";
    std::cout << "SORTED WITH BFS: " << gr::sort_bfs(slist) << "\n";
    std::cout << "SORTED WITH DFS: " << gr::sort_dfs(adjm) << "\n";
    std::cout << "SORTED WITH DFS: " << gr::sort_dfs(incm) << "\n";
    std::cout << "SORTED WITH DFS: " << gr::sort_dfs(plist) << "\n";
    std::cout << "SORTED WITH DFS: " << gr::sort_dfs(slist) << "\n\n";

    for (int i = 0; i < 4; i++) {
        const auto random = gr::amatrix_dir_graph::random(gr::random<int> (4, 8), gr::random<float> (0.3, 0.9));
        std::cout << gr::intercom::convert<gr::amatrix_dir_graph, gr::plist_dir_graph>(random) << std::endl;
    }
    return 0;
}