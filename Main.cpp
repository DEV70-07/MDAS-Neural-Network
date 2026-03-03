#include "NeuralNetwork.hpp"
#include "TrainingData.hpp"
#include <random>
#include <iostream>
#include <algorithm>

std::ostream &operator<<(std::ostream &os, const std::vector<double> &vec){
    os << "[";
    for (double val : vec){
        os << val << ", ";
    }
    
    return os << "]";
}

const int MAX_OP_NUMBER = 100;
const double MAX_OP_NORMALIZE = 200;

const int TRAIN_DATA_SIZE = 5000;
const int TRAIN_EPOCHS = 1000;

int main(){
    NeuralNetwork calc_network({2, 64, 64, 1});

    std::vector<TrainingData> training_data;

    training_data.resize(TRAIN_DATA_SIZE);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> numbers(-MAX_OP_NUMBER, MAX_OP_NUMBER);
    std::uniform_int_distribution operation(0, 3);

    std::cout << "Generating training data..." << std::endl;

    /*int sum_data = 0;
    int sub_data = 0;
    int mul_data = 0;
    int div_data = 0;

    for (size_t i = 0; i < TRAIN_DATA_SIZE; i++){
        TrainingData data;
        data.input.resize(6);
        data.output.resize(1);
        double number_a = numbers(rng);
        double number_b = numbers(rng);
        int op = operation(rng);

        if (op == 3 && std::abs(number_b) < 1.0){
            number_b = 1.0;
        }

        data.input[0] = number_a / MAX_OP_NUMBER;
        data.input[1] = number_b / MAX_OP_NUMBER;
        data.input[2 + op] = 1;

        switch (op)
        {
            case 0:
                sum_data++;
                data.output[0] = (number_a + number_b) / (MAX_OP_NORMALIZE);
                break;
            
            case 1:
                sub_data++;
                data.output[0] = (number_a - number_b) / (MAX_OP_NORMALIZE);
                break;

            case 2:
                mul_data++;
                data.output[0] = (number_a * number_b) / (MAX_OP_NORMALIZE);
                break;

            case 3:
                div_data++;
                data.output[0] = (number_a / number_b) / (MAX_OP_NORMALIZE);
                break;
            
            default:
                break;
        }

        training_data[i] = data;
    }*/

    for (size_t i = 0; i < TRAIN_DATA_SIZE; i++){
        TrainingData data;
        data.input.resize(2);
        data.output.resize(1);
        double number_a = numbers(rng);
        double number_b = numbers(rng);

        data.input[0] = number_a / MAX_OP_NUMBER;
        data.input[1] = number_b / MAX_OP_NUMBER;

        data.output[0] = (number_a + number_b) / (MAX_OP_NORMALIZE);


        training_data[i] = data;
    }

    //std::cout << "Training Data Generated!:\nTotal Sum Operations: " << sum_data << "\nTotal Subtraction Operations: " << sub_data << "\nTotal Multiplication Operations: " << mul_data << "\nTotal Division Operations: " << div_data << std::endl; 

    std::cout << "Training Neural Network..." << std::endl;

    for (size_t epoch = 0; epoch < TRAIN_EPOCHS; epoch++){
        //std::cout << "Epoch " << epoch << " / " << TRAIN_EPOCHS << std::endl;
        for (const TrainingData &data : training_data){
            calc_network.forward_layers(data.input);
            calc_network.train(data.output);
        }

        std::shuffle(training_data.begin(), training_data.end(), rng);
    }

    

    std::cout << "Your turn..." << std::endl;

    while (1){
        std::vector<double> input;
        input.resize(2);

        double number_a, number_b;
        char op;

        std::cout << "Your number: ";

        if (!(std::cin >> number_a >> op >> number_b)){
            std::cin.clear();
            std::cin >> op;
            if (op == 'n'){
                std::cout << calc_network << std::endl;
                continue;
            }else if (op == 't'){
                for (size_t epoch = 0; epoch < TRAIN_EPOCHS; epoch++){
                    //std::cout << "Epoch " << epoch << " / " << TRAIN_EPOCHS << std::endl;
                    for (const TrainingData &data : training_data){
                        calc_network.forward_layers(data.input);
                        calc_network.train(data.output);
                    }

                    std::shuffle(training_data.begin(), training_data.end(), rng);
                }

                continue;
            }
            else break;
        }


        input[0] = number_a / MAX_OP_NUMBER;
        input[1] = number_b / MAX_OP_NUMBER;

        
        std::cout << input << std::endl;
        std::cout << "\n" << calc_network.forward_layers(input)[0] * MAX_OP_NORMALIZE << std::endl;
 
    }

    /*while (1){
        std::vector<double> input;
        input.resize(6);

        double number_a, number_b;
        char op;

        std::cout << "Your number: ";

        if (!(std::cin >> number_a >> op >> number_b)){
            if (op == 'n') std::cout << calc_network << std::endl;
            else break;
        }

        std::cout << number_a << " " << op << " " << number_b << std::endl; 

        input[0] = number_a / MAX_OP_NUMBER;
        input[1] = number_b / MAX_OP_NUMBER;

        switch (op)
        {
            case '+':
                input[2] = 1;
                break;
            
            case '-':
                input[3] = 1;
                break;
            
            case '*':
                input[4] = 1;
                break;
            
            case '/':
                input[5] = 1;
                break;
            
            default:
                break;
        }
        std::cout << input << std::endl;
        std::cout << "\n" << calc_network.forward_layers(input)[0] * MAX_OP_NORMALIZE << std::endl;
 
    }*/

    return 0;
}