#ifndef AISD_UTIL_HPP
#define AISD_UTIL_HPP

namespace gr {

    template<typename _Tp>
    std::string vec_str(const std::vector<_Tp>& __vec) {
        std::stringstream ss;
        for (const auto& x : __vec) ss << x << " ";
        return ss.str();
    }

#define scan(collection) (collection).begin(), (collection).end()
}

#endif //AISD_UTIL_HPP
