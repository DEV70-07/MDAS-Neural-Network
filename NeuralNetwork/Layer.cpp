#include "Layer.hpp"
#include "Activations.hpp"
#include "Constants.hpp"
#include <random>
#include <iostream>

Layer::Layer(size_t i, size_t n, bool act):weight_matrix(i + 1, n), delta(n), backwards_error(i + 1), minibatch_weights(i + 1, n), last_output(n), last_input(i), neurons(n), inputs(i), use_activation(act){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> dist(conf::MIN_RANDOM_WEITGHT, conf::MAX_RANDOM_WEIGHT);
    
    for (int pos = 0; pos < (i + 1) * n; pos++){
        weight_matrix[pos] = dist(rng);
    }
}

const std::vector<double>& Layer::forward(const std::vector<double>& i){
    if (i.size() != inputs){
        std::cerr << "Input Size Not Matches Layer Size." << std::endl;
        exit(1);
    }

    last_input = i;
    last_input.push_back(1.0);
    
    weight_matrix.buffer_multiply(last_input, last_output);

    if (!use_activation){
        return last_output;
    }

    for (size_t o = 0; o < neurons; o++){
        last_output[o] = ReLU(last_output[o]);
    }

    return last_output;
}

const std::vector<double> &Layer::backpropagate(const std::vector<double> &e){

    //Delta Calc:

    for (size_t d = 0; d < delta.size(); d++){
        delta[d] = use_activation ? e[d] * ReLU_derivate(last_output[d]) : e[d];
    }

    //Weight Update:

    for (size_t c = 0; c < neurons; c++){
        for (size_t r = 0; r < inputs + 1; r++){
            minibatch_weights(r, c) += last_input[r] * delta[c];
        }
    }

    //Backwards Error:
    
    weight_matrix.transpose_buffer_multiply(delta, backwards_error);


    return backwards_error;
}

void Layer::update_weights(size_t batch_size)
{
    double wmul = 1.0 / batch_size * conf::LEARNING_RATE;
    for (size_t w = 0; w < weight_matrix.size(); w++){
        weight_matrix[w] -= minibatch_weights[w] * wmul; 
        minibatch_weights[w] = 0;
    }
}

const std::vector<double> &Layer::get_last_output() const
{
    return last_output;
}

const std::vector<double> &Layer::get_last_input() const
{
    return last_input;
}

size_t Layer::size() const
{
    return weight_matrix.size();
}

std::ostream& operator<<(std::ostream& os, const Layer& l){
    return os << l.weight_matrix;
}
