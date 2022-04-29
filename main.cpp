#include <graphlib>
#include <iostream>

int main() {

    gr::enable_bool_string();

    auto amatrix = gr::adjacency_matrix_dir_graph::random(6, 0.67);
    std::cout << "DŻENEREJTED MEJTRIX SOMSIEDZTWA\n" << amatrix << std::endl;
    std::cout << "POSORTED WITH BFS\n" << gr::vec_str(gr::sort_bfs((amatrix))) << std::endl;
    std::cout << "POSORTED WITH DFS\n" << gr::vec_str(gr::sort_dfs((amatrix))) << std::endl << std::endl;

    auto slist = gr::successors_list_dir_graph::from_adjacency_matrix(amatrix);
    std::cout << "LISTA OF NASTEMPNIKI\n" << slist << std::endl;
    std::cout << "POSORTED WITH BFS\n" << gr::vec_str(gr::sort_bfs((slist))) << std::endl;
    std::cout << "POSORTED WITH DFS\n" << gr::vec_str(gr::sort_dfs((slist))) << std::endl << std::endl;
//
    auto plist = gr::predecessors_list_dir_graph::from_adjacency_matrix(amatrix);
    std::cout << "LISTA OF POPRZEDNIKI\n" << plist << std::endl;
    std::cout << "POSORTED WITH BFS\n" << gr::vec_str(gr::sort_bfs((plist))) << std::endl;
    std::cout << "POSORTED WITH DFS\n" << gr::vec_str(gr::sort_dfs((plist))) << std::endl << std::endl;

    auto imatrix = gr::incidence_matrix_dir_graph::from_adjacency_matrix(amatrix);
    std::cout << "MEJTRIX INCYDENCJI\n" << imatrix << "\n";
    std::cout << "POSORTED WITH BFS\n" << gr::vec_str(gr::sort_bfs((imatrix))) << std::endl;
    std::cout << "POSORTED WITH DFS\n" << gr::vec_str(gr::sort_dfs((imatrix))) << std::endl << std::endl;

    /*
    /// Macierz somsiedztwa
    //                                0  1  2  3  4  nr wierzchołka
    gr::adjacency_matrix_graph am = {{0, 1, 1, 0, 1},  // 0
                                     {1, 0, 1, 1, 1},  // 1
                                     {1, 1, 0, 1, 0},  // 2
                                     {0, 1, 1, 0, 1},  // 3
                                     {1, 1, 0, 1, 0}}; // 4
    std::cout << "Testing adjacency matrix graph\n";
    std::cout << "Edge between vertex 4 and 1: " << am.connected(4, 1) << '\n';
    std::cout << "Edge between vertex 3 and 2: " << am.connected(3, 2) << '\n';
    std::cout << "Edge between vertex 2 and 4: " << am.connected(2, 4) << '\n';
    std::cout << am;

    /// Macierz somsiedztwa (skierowana)
    //                                     0   1   2   3   4  nr wierzchołka
    gr::adjacency_matrix_dir_graph amd = {{0,  1,  -1, 0,  -1}, // 0
                                          {-1, 0,  -1, 1,  1},  // 1
                                          {1,  1,  0,  -1, 0},  // 2
                                          {0,  -1, 1,  0,  -1}, // 3
                                          {1,  -1, 0,  1,  0}}; // 4
    std::cout << "\nTesting adjacency matrix graph (directed)\n";
    std::cout << "Edge between vertex 4 and 1: " << amd.connected(4, 1) << '\n';
    std::cout << "Edge between vertex 2 and 2: " << amd.connected(2, 2) << '\n';
    std::cout << "Edge between vertex 1 and 3: " << amd.connected(1, 3) << '\n';

    /// Macierz incydencji
    //                 nr krawędzi -> 0  1  2  3  4  5  6  7       ↓ nr wierzchołka
    gr::incidence_matrix_graph im = {{1, 1, 1, 0, 0, 0, 0, 0},  // 0
                                     {1, 0, 0, 1, 1, 1, 0, 0},  // 1
                                     {0, 1, 0, 1, 0, 0, 1, 0},  // 2
                                     {0, 0, 0, 0, 0, 1, 1, 1},  // 3
                                     {0, 0, 1, 0, 1, 0, 0, 1}}; // 4
    std::cout << "\nTesting incidence matrix graph\n";
    std::cout << "Edge between vertex 4 and 2: " << im.connected(4, 2) << '\n';
    std::cout << "Edge between vertex 1 and 4: " << im.connected(1, 4) << '\n';
    std::cout << "Edge between vertex 2 and 3: " << im.connected(2, 3) << '\n';

    /// Macierz incydencji (skierowana)
    //                      nr krawędzi -> 0   1   2   3   4   5   6   7        ↓ nr wierzchołka
    gr::incidence_matrix_dir_graph imd = {{-1, 1,  1,  0,  0,  0,  0,  0},   // 0
                                          {1,  0,  0,  1,  -1, -1, 0,  0},   // 1
                                          {0,  -1, 0,  -1, 0,  0,  1,  0},   // 2
                                          {0,  0,  0,  0,  0,  1,  -1, 1},   // 3
                                          {0,  0,  -1, 0,  1,  0,  0,  -1}}; // 4
    std::cout << "\nTesting incidence matrix graph (directed)\n";
    std::cout << "Edge between vertex 1 and 4: " << imd.connected(1, 4) << '\n';
    std::cout << "Edge between vertex 2 and 3: " << imd.connected(2, 3) << '\n';
    std::cout << "Edge between vertex 4 and 2: " << imd.connected(4, 2) << '\n';

    /// Lista krawędzi
    //                    poł. wierzchołki
    gr::edges_list_graph vl = {{0, 1},  // 0 <- nr krawędzi
                               {0, 2},  // 1
                               {0, 4},  // 2
                               {1, 2},  // 3
                               {1, 3},  // 4
                               {1, 4},  // 5
                               {2, 3},  // 6
                               {3, 4}}; // 7
    std::cout << "\nTesting edges list graph\n";
    std::cout << "Edge between vertex 4 and 0: " << vl.connected(4, 0) << '\n';
    std::cout << "Edge between vertex 2 and 3: " << vl.connected(2, 3) << '\n';
    std::cout << "Edge between vertex 0 and 3: " << vl.connected(0, 3) << '\n';

    /// Lista krawędzi (skierowana)
    //                         poł. wierzchołki
    gr::edges_list_dir_graph vld = {{0, 1},  // 0 <- nr krawędzi
                                    {1, 3},  // 1
                                    {1, 4},  // 2
                                    {2, 0},  // 3
                                    {2, 1},  // 4
                                    {3, 2},  // 4
                                    {4, 0},  // 5
                                    {4, 3}}; // 6
    std::cout << "\nTesting edges list graph (directed)\n";
    std::cout << "Edge between vertex 4 and 0: " << vld.connected(4, 0) << '\n';
    std::cout << "Edge between vertex 2 and 3: " << vld.connected(2, 3) << '\n';
    std::cout << "Edge between vertex 2 and 1: " << vld.connected(2, 1) << '\n';

    /// Lista incydencji / somsiedztwa
    //                    nr wierzchołka ↓  somsiedzi
    gr::incidency_list_dir_graph ild = {{1, 2, 3, 5},
                                        {2, 1, 3, 4, 5},
                                        {3, 1, 2, 4},
                                        {4, 2, 3, 5},
                                        {5, 1, 2, 4}};

    /// Lista następników
    //                     nr wierzchołka ↓  następniki
    gr::successors_list_dir_graph sld = {{1, 2},
                                         {2, 4, 5},
                                         {3, 1, 2},
                                         {4, 3},
                                         {5, 1, 4}};

    /// Lista poprzedników
    //                       nr wierzchołka ↓  poprzedniki
    gr::predecessors_list_dir_graph pld = {{1, 3, 5},
                                           {2, 1, 3},
                                           {3, 4},
                                           {4, 2, 5},
                                           {5, 2}};

    /// Macierz grafu
    //              nr wierzchołka ->  0   1   2   3   4   kolumny dod.  ↓ nr wierzchołka
    gr::graph_matrix_dir_graph gmd = {{-4, 2,  10, -4, 10, 2, 3, 1},  // 0
                                      {8,  -2, 8,  5,  5,  4, 1, 2},  // 1
                                      {2,  2,  -5, 9,  -5, 1, 4, 3},  // 2
                                      {-4, 10, 3,  -4, 10, 3, 2, 1},  // 3
                                      {4,  7,  -5, 4,  -5, 1, 2, 3}}; // 4
    */

    return 0;
}