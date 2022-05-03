#ifndef GRAPHLIB_MATRIX_HPP
#define GRAPHLIB_MATRIX_HPP

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

        matrix(const std::initializer_list<std::vector<Tp>>& init) {
            for (const auto& row : init) matrix_vector.push_back(row);
        }

        explicit matrix(const std::vector<std::vector<Tp>>& vector) {
            matrix_vector = vector;
        }

        matrix(const matrix<Tp>& matrix) {
            matrix_vector = matrix.matrix_vector;
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

        [[nodiscard]] const_iterator begin() const {
            return matrix_vector.begin();
        }

        iterator begin() {
            return matrix_vector.begin();
        }

        [[nodiscard]] const_iterator end() const {
            return matrix_vector.end();
        }

        iterator end() {
            return matrix_vector.end();
        }

        template<typename Target, typename Map>
        [[nodiscard]] matrix<Target> map(const Map& mapper) const {
            matrix<Target> matrix(size_rows(), size_cols());
            auto matrix_row = matrix.begin();
            for (const auto& row : *this) {
                auto matrix_row_cell = matrix_row++->begin();
                for (const auto& cell : row) *matrix_row_cell++ = mapper(cell);
            }
            return matrix;
        }

        template<typename Acc>
        [[nodiscard]] std::vector<Tp> reduce_cols(const Acc& accumulator) const {
            std::vector<Tp> vector(size_cols());
            for (const auto& row : *this) {
                auto vector_cell = vector.begin();
                for (const auto& cell : row) {
                    *vector_cell = accumulator(*vector_cell, cell);
                    vector_cell++;
                }
            }
            return vector;
        }

        [[nodiscard]] virtual std::string str() const {
            const matrix<size_t> widths =
                    this->map<size_t>([](const Tp& cell) { return (std::stringstream{} << cell).str().size(); });
            const std::vector<size_t> col_widths =
                    widths.reduce_cols([](size_t max, size_t width) { return std::max(max, width); });
            std::stringstream ss;
            auto widths_row = widths.begin();
            for (const auto& row : *this) {
                auto widths_row_cell = widths_row++->begin(),
                        col_widths_cell = col_widths.begin();
                for (const auto& cell : row) {
                    const size_t spaces = *col_widths_cell++ - *widths_row_cell++;
                    for (int i = 0; i < spaces; i++) ss << ' ';
                    ss << cell << ' ';
                }
                ss << '\n';
            }
            return ss.str();
        }
    };

    template<typename _Tp>
    std::ostream& operator<<(std::ostream& out, const matrix<_Tp>& matrix) {
        return out << matrix.str();
    }

}

#endif //GRAPHLIB_MATRIX_HPP