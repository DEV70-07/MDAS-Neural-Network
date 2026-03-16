#include "NeuralNetwork.hpp"
#include "Layer.hpp"
#include "Constants.hpp"
#include <iostream>


NeuralNetwork::NeuralNetwork(const std::vector<size_t> &layers): train_counter(0), error(layers.back()){
    size_t total_layers = layers.size() - 1;

    for (size_t l = 0; l < total_layers; l++){
        this->layers.push_back(Layer(layers[l], layers[l + 1], l != (total_layers - 1)));
    }
}

std::vector<double> NeuralNetwork::forward_layers(const std::vector<double> &i){
    std::vector<double> last_output = i;
    
    for (size_t l = 0; l < layers.size(); l++){
        last_output = layers[l].forward(last_output);
    }
    return last_output;
}

void NeuralNetwork::train(const std::vector<double> &expected){
    train_counter++;
    const std::vector<double> &last_output = layers.back().get_last_output();

    //double loss = 0;

    for (size_t e = 0; e < last_output.size(); e++){
        error[e] = last_output[e] - expected[e]; 
        //loss += std::pow(error[e], 2);
    }

    //std::cout << "Loss: " << (loss / last_output.size()) << std::endl;
    for (int l = layers.size() - 1; l >= 0 ; l--){
        error = layers[l].backpropagate(error);
    }

    if (train_counter >= conf::BATCH_SIZE){
        update_layer_weights(conf::BATCH_SIZE);
        train_counter = 0;
    }

}

void NeuralNetwork::update_layer_weights(size_t batch_size)
{
    for (Layer &layer : layers){
        layer.update_weights(batch_size);
    }
}

std::ostream& operator<<(std::ostream& os, const NeuralNetwork& nn){
    for (size_t l = 0; l < nn.layers.size(); l++){
        os << "#Layer " << l << " (" << nn.layers[l].size() << " weights):\n" << nn.layers[l] << "\n";  
    }
    return os;
}