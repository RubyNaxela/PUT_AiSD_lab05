#ifndef GRAPHLIB_UTIL_HPP
#define GRAPHLIB_UTIL_HPP

#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace gr {

    void enable_bool_string() {
        std::cout << std::boolalpha;
    }

    template<typename Tp>
    std::string vec_str(const std::vector<Tp>& vec) {
        std::stringstream ss;
        for (const auto& x : vec) ss << x << " ";
        return ss.str();
    }

    template<typename Dur>
    requires std::chrono::__is_duration<Dur>::value
    class timer {

        std::chrono::time_point<std::chrono::high_resolution_clock, Dur> start_point, end_point;
        bool running = false;

    public:

        timer() {
            start_point = std::chrono::high_resolution_clock::now();
            end_point = std::chrono::high_resolution_clock::now();
            running = false;
        }

        std::chrono::time_point<std::chrono::high_resolution_clock, Dur> now() const {
            return std::chrono::high_resolution_clock::now();
        }

        void start() {
            if (!running) {
                running = true;
                start_point = now();
            } else throw std::runtime_error("Illegal timer state: timer is already running");
        }

        void stop() {
            if (running) {
                end_point = now();
                running = false;
            } else throw std::runtime_error("Illegal timer state: timer is not running");
        }

        int get_measured_time() {
            Dur time = std::chrono::duration_cast<Dur>(end_point - start_point);
            return time.count();
        }

        std::string unit() {
            constexpr intmax_t denominator = Dur::period::den;
            if (denominator == 1) return "s";
            else if (denominator == 1000) return "ms";
            else if (denominator == 1000000) return "us";
            else if (denominator == 1000000000) return "ns";
            return "?";
        }
    };

    typedef std::chrono::duration<double, std::nano> precision_ns;
    typedef std::chrono::duration<double, std::micro> precision_us;
    typedef std::chrono::duration<double, std::milli> precision_ms;
    typedef std::chrono::duration<double, std::ratio<1, 1>> precision_s;

#define whole(collection) (collection).begin(), (collection).end()
#define not_found (-1)
#define is_found != (-1)
#define is_not_found == (-1)
}

#endif //GRAPHLIB_UTIL_HPP
