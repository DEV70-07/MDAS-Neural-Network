#include "Activations.hpp"

double ReLU(double x){
    return (x > 0.0) ? x : 0.0;
}

double ReLU_derivate(double x){
    return (x > 0.0) ? 1.0 : 0.0;
}
