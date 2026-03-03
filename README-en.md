# MDAS-Neural-Network
My Dumb And Slow Neural Network

Well, I randomly felt like making a neural network in C, C++, or Python. After hours (maybe seconds...) checking points in each language, I randomly chose C++. Well, I got down to work, learned about matrices, and started implementing this class, as in Matrix.cpp (and .hpp). then I learned more concepts about neural networks, so I made Layer.cpp, NeuralNetwork.cpp Activations.cpp, and Constants. hpp. Well, there's also Main.cpp. I initially planned to make a neural network that could learn addition, subtraction, multiplication, and division, but in my first attempts, the neural network failed dramatically. Since I didn't know if it was a problem with my code or with the training data (maybe both), I decided to simplify things. after a while, the network learned addition surprisingly well, it was even fast and smart enough for me to try to go back to the old system of addition, subtraction, multiplication, and division, but then I thought I might need more performance and implemented a Minibatch system, and well, I still need to implement multithreading

I definitely wrote some terrible code in Main.cpp because it's basically just for testing the rest of the other code. To compile, you need g++. I did this on Windows, so I ran the command:

`g++ -O3 Main.cpp Matrix.cpp Layer.cpp Activations.cpp NeuralNetwork.cpp -o NeuralNetwork.exe` 

This should work for you if you are on Windows. As I haven't used Linux in a long time, I'm not sure how you can compile this there. Below is a brief explanation of how the concepts I used work (in my opinion):

# Matrix.hpp / Matrix.cpp

Well, there's not much of a secret here. Matrix is mainly used to store and multiply the weights of the Layers and, consequently, of the neural network itself. Before, I used the multiplication operator here, which created the output `std::vector<double>` and returned it, but I saw that this was slowing down my code, so I implemented two functions:

`Matrix::buffer_multiply`, which basically multiplies the input elements by the rows of the matrix, then adds the rows of each column individually, and this goes to the output vector. I used the formula `r * cols + c` to access a one-dimensional vector (in this case, the data) as if it were two-dimensional (a matrix, in fact). this should be faster than having one vector inside another vector

`Matrix::transpose_buffer_multiply`, this one always ties my brain in knots, but it basically does the same thing as the normal buffer_multiply, the only difference is that it uses the width of the matrix as height, and vice versa, and the formula for accessing the data changes to `c * cols + r`. It's as if I had actually rotated the matrix, but in fact I'm just accessing the data in a different way. It is mainly used in the Layer backpropagate. 

In this file, I think the most interesting concepts are just that

# Layer.hpp / Layer.cpp

This one has some very interesting things. Part of the code's slowness is hidden in `Layer::backpropagate`, so much so that I implemented minibatch in the hope that it would somehow solve the problem, but it didn't. Now it has two matrices, one that stores its weights, and the other that stores the modifications that must be applied using `Layer::update_weights`. The minibatch made it slower, but more ready to implement multithreading in the future. Well, there aren't that many interesting things to say about the code here. It's almost like a bridge between NeuralNetwork and Matrix, but it's at least cool to see how things fit together. Although not very interesting, it implements the most used functions during training and during the use of the network itself. They are:

`Layer::forward`, which basically multiplies the inputs by the weights using `Matrix::buffer_multiply`, and returns this to either be shown to the user or be used by NeuralNetwork to feed the next layers. This also saves the input and output to be used later during network training.

`Layer::backpropagate`, this one takes up most of your time. Well, when training a network with 2 inputs, 2 hidden layers, 64 neurons each, and one output, with about 5,000 training data points, it takes about 40 seconds to run 1,000 epochs on my hardware (with the -O3 flag in the compiler). Of those 40 seconds, about 15 seconds are exclusively from this function. Why? I don't know, but certainly [VerySleppy](https://github.com/VerySleepy/verysleepy) lied about something, but I still know that this function is not optimized as it should be.

# NeuralNetwork.hpp / NeuralNetwork.cpp

This one controls the Layers, which control the Matrices, which control the weights. It can be initialized with a std::vector<size_t> according to the network structure you want. For example, if you want a network with 6 inputs, 32 neurons in one hidden layer, 16 in another, 5 in another, and finally 1 output (why would you want a network like that?), you can use it like this:

```Cpp
NeuralNetwork neural({6, 32, 16, 5, 1});
```

It is quite flexible and takes care of creating layers, and its `NeuralNetwork::train` uses the automatic minibatch system, so you need to call the `NeuralNetwork::train` function at least `conf::BATCH_SIZE` times to notice any difference. I think maybe I should simplify the training logic, so that instead of having to call the `NeuralNetwork::forward_layers` function, you can simply call the `NeuralNetwork::train` function, passing a TrainingData to it.

Of course, I couldn't talk much about this network here, but if you want to talk about it, or are simply interested in having a programmer friend (who is often busy working and is definitely not experienced in any language), you can contact me through any of my social media accounts:

Instagram (most active): joel20.09
Discord (not very active): \_de.v\_
And although rarely used Email: joelbergue.dev@gmail.com
