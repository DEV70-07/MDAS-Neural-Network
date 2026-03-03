#include "Matrix.hpp"
#include <iostream>

Matrix::Matrix(size_t r, size_t c):rows(r), cols(c){
    data.assign(rows * cols, 1.0);
}

std::vector<double> Matrix::operator*(const std::vector<double>& input) const{
    std::vector<double> out(cols); 

    buffer_multiply(input, out);

    return out;
}

void Matrix::buffer_multiply(const std::vector<double> &input, std::vector<double> &output) const
{
    if (input.size() != rows || output.size() != cols){
        std::cerr << "Input or output Size Not Match. " << input.size() << " != " << rows << " or " << output.size() << " != " << cols << std::endl;
        exit(1);
    }

    for (size_t c = 0; c < cols; c++){
        double neuron_value = 0;
        for (size_t r = 0; r < rows; r++){ 
            neuron_value += input[r] * data[r * cols + c];
        }
        output[c] = neuron_value;
    }
}

void Matrix::transpose_buffer_multiply(const std::vector<double> &input, std::vector<double> &output)
{
    if (input.size() != cols || output.size() != rows){
        std::cerr << "Input or output Size Not Match. " << input.size() << " != " << cols << " or " << output.size() << " != " << rows << std::endl;
        exit(1);
    }


    for (size_t c = 0; c < rows; c++){
        double neuron_value = 0;
        for (size_t r = 0; r < cols; r++){ 
            neuron_value += input[r] * data[c * cols + r];
        }
        output[c] = neuron_value;
    }
}

//Output[c] = 10
//Output[c] -= Output[c]
double& Matrix::operator()(size_t r, size_t c)
{
    return data[r * cols + c];
}

const double Matrix::operator()(size_t r, size_t c) const
{
    return data[r * cols + c];
}

double &Matrix::operator[](size_t pos)
{
    return data[pos];
}

size_t Matrix::size() const
{
    return data.size();
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
    os << "[\n";
    for (size_t r = 0; r < matrix.rows; r++){
        os << "  ";
        for (size_t c = 0; c < matrix.cols; c++){
            os << matrix(r, c) << ", ";
        }
        os << "\n";
    }

    return os << "]";
}