#ifndef NEURAL_NETWORK_HPP
#include <iosfwd>
#include <vector>
#include "Layer.hpp"
#define NEURAL_NETWORK_HPP
class NeuralNetwork{
    std::vector<Layer> layers;
    size_t train_counter;
    std::vector<double> error;
    public:

    NeuralNetwork(const std::vector<size_t> &l);
    std::vector<double> forward_layers(const std::vector<double>& i);
    void train(const std::vector<double> &expected);
    friend std::ostream& operator<<(std::ostream& os, const NeuralNetwork& nn);
    void update_layer_weights(size_t batch_size);
};
#endif