#include <graphlib>
#include "test.hpp"

int main() {

    const auto test_data = test::random_data({5, 20, 50}, {0.25, 0.5, 0.9}, 10);
    std::cout << "\n=== Adjacency matrix ===\n";
    test::run_test<gr::adjacency_matrix_dir_graph>(test_data);
    std::cout << "\n=== Incidence matrix ===\n";
    test::run_test<gr::incidence_matrix_dir_graph>(test_data);
    std::cout << "\n=== Successors list ===\n";
    test::run_test<gr::successors_list_dir_graph>(test_data);
    std::cout << "\n=== Predecessors list ===\n";
    test::run_test<gr::predecessors_list_dir_graph>(test_data);

    return 0;
}