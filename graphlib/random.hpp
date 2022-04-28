#ifndef AISD_RANDOM_HPP
#define AISD_RANDOM_HPP
#pragma ide diagnostic ignored "cert-err58-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"
#pragma ide diagnostic ignored "cert-msc32-c"

#include <ctime>
#include <random>
#include <type_traits>

namespace gr {

    bool random_bool(float chance_for_true);

    struct random {

        random() = delete;

        inline static std::default_random_engine engine{static_cast<unsigned int>(time(nullptr))};
    };

    template<typename _Tp>
    requires std::is_integral_v<_Tp>
    _Tp random(const _Tp __min, const _Tp __max) {
        return std::uniform_int_distribution<_Tp>{__min, __max}(random::engine);
    }

    template<class _Tp>
    requires std::is_floating_point_v<_Tp>
    _Tp random(const _Tp __min, const _Tp __max) {
        return std::uniform_real_distribution<_Tp>{__min, __max}(random::engine);
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

}

#endif //AISD_RANDOM_HPP