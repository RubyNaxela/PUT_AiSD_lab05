#ifndef GRAPHLIB_RANDOM_HPP
#define GRAPHLIB_RANDOM_HPP
#pragma ide diagnostic ignored "cert-err58-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc32-c"

#include <ctime>
#include <random>
#include <type_traits>
#include <amgraph.hpp>

namespace gr {

    bool random_bool(float chance_for_true);

    struct random {

        random() = delete;

        inline static std::default_random_engine engine{static_cast<unsigned int>(time(nullptr))};
    };

    template<typename _Tp>
    requires std::is_integral_v<_Tp>
    _Tp random(const _Tp min, const _Tp max) {
        return std::uniform_int_distribution<_Tp>{min, max}(random::engine);
    }

    template<class _Tp>
    requires std::is_floating_point_v<_Tp>
    _Tp random(const _Tp min, const _Tp max) {
        return std::uniform_real_distribution<_Tp>{min, max}(random::engine);
    }

    template<typename _Tp>
    requires std::is_floating_point_v<_Tp>
    _Tp random() {
        return std::uniform_real_distribution<_Tp>{0, 1}(random::engine);
    }

    template<typename _Tp>
    requires std::is_same_v<_Tp, bool>
    _Tp random() {
        return std::uniform_int_distribution<_Tp>{0, 1}(random::engine);
    }

    bool random_bool(float chance_for_true) {
        return random<float>(0, 1) <= chance_for_true;
    }

    template<typename Gr>
    requires std::is_base_of_v<amatrix_dir_graph, Gr>
    Gr random_dag(int vertices, float fill) {
        std::vector<std::vector<int>> vec(vertices);
        for (int i = 0; i < vertices; ++i) {
            for (int j = i; j < vertices; ++j) {
                if (i == j) vec[i].push_back(0);
                else if (j > i) {
                    int random_0_or_1 = gr::random_bool(fill);
                    vec[i].push_back(random_0_or_1);
                    vec[j].push_back(random_0_or_1 == 1 ? -1 : 0);
                }
            }
        }
        std::vector<int> shuffled_indices(vertices);
        std::iota(shuffled_indices.begin(), shuffled_indices.end(), 0);
        std::shuffle(shuffled_indices.begin(), shuffled_indices.end(), gr::random::engine);
        gr::matrix<int> matrix(vertices, vertices);
        int r = 0;
        for (int row_index : shuffled_indices) {
            int c = 0;
            for (int col_index : shuffled_indices) matrix[r][c++] = vec[row_index][col_index];
            r++;
        }
        return Gr(matrix);
    }

    template<typename Gr>
    requires std::is_base_of_v<graph, Gr> and (not std::is_base_of_v<amatrix_dir_graph, Gr>)
    Gr random_dag(int vertices, float fill) {
        return intercom::convert<amatrix_dir_graph, Gr>(random_dag<amatrix_dir_graph > (vertices, fill));
    }
}

#endif //GRAPHLIB_RANDOM_HPP