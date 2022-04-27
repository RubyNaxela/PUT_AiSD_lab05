#ifndef AISD_BOOLSTR_HPP
#define AISD_BOOLSTR_HPP

#include <iostream>

namespace gr {
    void enable_bool_string() {
        std::cout << std::boolalpha;
    }
}

#endif //AISD_BOOLSTR_HPP