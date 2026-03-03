#ifndef MATRIX_HPP
#include <vector>
#include <iosfwd>

#define MATRIX_HPP
class Matrix{
    std::vector<double> data;

    size_t rows;
    size_t cols;

    public:

    Matrix(size_t r, size_t c);

    std::vector<double> operator*(const std::vector<double>& input) const;

    void buffer_multiply(const std::vector<double>& input, std::vector<double>& output) const;
    void transpose_buffer_multiply(const std::vector<double>& input, std::vector<double>& output);
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    double& operator()(size_t r, size_t c);
    const double operator()(size_t r, size_t c) const;
    double& operator[](size_t pos);
    
    size_t size() const;
};

std::ostream& operator<<(std::ostream &os, const std::vector<double> &vec);
#endif