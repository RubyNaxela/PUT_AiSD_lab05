#ifndef AISD_MATRIX_HPP
#define AISD_MATRIX_HPP

#pragma ide diagnostic ignored "OCDFAInspection"

#include <vector>
#include <sstream>
#include <string>

namespace gr {

    template<typename Tp>
    class matrix {

        std::vector<std::vector<Tp>> matrix_vector;

    public:

        typedef typename std::vector<std::vector<Tp>>::const_iterator const_iterator;
        typedef typename std::vector<std::vector<Tp>>::iterator iterator;

        matrix() = default;

        matrix(const std::initializer_list<std::vector<Tp>>& __init) {
            for (const auto& row : __init) matrix_vector.push_back(row);
        }

        explicit matrix(const std::vector<std::vector<Tp>>& __init) {
            matrix_vector = __init;
        }

        matrix(const matrix<Tp>& __matrix) {
            matrix_vector = __matrix.matrix_vector;
        }

        matrix(int rows, int cols) {
            for (int i = 0; i < rows; i++) matrix_vector.emplace_back(cols);
        }

        [[nodiscard]] std::vector<Tp>& operator[](int n) {
            return matrix_vector[n];
        }

        [[nodiscard]] std::vector<Tp> operator[](int n) const {
            return matrix_vector[n];
        }

        void erase_row(const_iterator it) {
            matrix_vector.erase(it);
        }

        void erase_row(size_t index) {
            matrix_vector.erase(matrix_vector.begin() + index);
        }

        void erase_column(size_t index) {
            for (auto& row : *this) row.erase(row.begin() + index);
        }

        [[nodiscard]] size_t size_rows() const {
            return matrix_vector.size();
        }

        [[nodiscard]] size_t size_cols() const {
            return matrix_vector[0].size();
        }

        const_iterator begin() const {
            return matrix_vector.begin();
        }

        iterator begin() {
            return matrix_vector.begin();
        }

        const_iterator end() const {
            return matrix_vector.end();
        }

        iterator end() {
            return matrix_vector.end();
        }

        [[nodiscard]] std::string str() const {
            std::stringstream ss;
            for (const auto& row : *this) {
                for (const auto& cell : row) {
                    std::stringstream cellss;
                    cellss << cell;
                    if (cellss.str().length() == 1) ss << ' ';
                    ss << cell << ' ';
                }
                ss << '\n';
            }
            return ss.str();
        }
    };

    template<typename _Tp>
    std::ostream& operator<<(std::ostream& __out, const matrix<_Tp>& __matrix) {
        return __out << __matrix.str();
    }

}

#endif //AISD_MATRIX_HPP