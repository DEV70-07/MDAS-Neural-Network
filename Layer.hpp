#ifndef LAYER_HPP
#include "Matrix.hpp"
#define LAYER_HPP
class Layer{
    size_t inputs;
    size_t neurons;
    std::vector<double> last_input;
    std::vector<double> last_output;
    Matrix weight_matrix;

    Matrix minibatch_weights;

    public:

    bool use_activation = true;
    
    Layer(size_t i, size_t n, bool act = 1);

    const std::vector<double>& forward(const std::vector<double> &i);

    friend std::ostream& operator<<(std::ostream& os, const Layer& l);

    std::vector<double> backpropagate(const std::vector<double> &e);

    void update_weights(size_t batch_size);

    const std::vector<double> &get_last_output() const;
    const std::vector<double> &get_last_input() const;

    size_t size() const;
};

#endif