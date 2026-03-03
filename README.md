# MDAS-Neural-Network
My Dumb And Slow Neural Network

Bem, aleatoriamente me bateu uma vontade de fazer uma rede neural em C, C++ ou Python, após horas (talvez segundos...) verificando pontos de cada linguagem, eu aleatóriamente escolhi C++, bem, puz a mão na massa, aprendi sobre Matrizes, e comecei implementando essa classe, como no Matrix.cpp (e .hpp), depois fui aprendendo mais conceitos sobre redes neurais, fiz assim a Layer.cpp, NeuralNetwork.cpp Activations.cpp e Constants.hpp, bem, tem também o Main.cpp, eu planejava inicialmente fazer uma rede neural que pudesse aprender somas, subtrações, multiplicações e divisões, mas nas minhas primeiras tentativas a rede neural falhou drasticamente, e como não sabia se era um problema com meus códigos ou com os dados de treinamento (talvez os dois), resolvi simplificar as coisas, depois de um tempo a rede aprendeu surpreendentemente bem somas, ela até que estava rápida e esperta o bastante para mim tentar voltar ao antigo sistema de soma, subtração, multiplicação e divisão, mas aí eu achei que podia precisar de mais performance e implementei um sistema de Minibatch, e bem, ainda preciso implementar multithreading

Eu definitivamente fiz um código horrível no Main.cpp porque ele é basicamente apenas para testar o resto dos outros códigos, para compilar você precisa ter o g++, eu fiz isso pelo Windows então rodei o comando:

`g++ -O3 Main.cpp Matrix.cpp Layer.cpp Activations.cpp NeuralNetwork.cpp -o NeuralNetwork.exe`

Isso deve funcionar para você se estiver no Windows, como faz um bom tempo que não uso Linux, não sei ao certo como você pode compilar isso por lá, abaixo uma breve explicação sobre como os conceitos que eu usei funcionam (na minha opinião):

# Matrix.hpp / Matrix.cpp

Bem, aqui não tem muito segredo, a Matrix é usada principalmente para guardar e multiplicar os pesos das Layers e consequentemente da rede neural em sí, antes eu usava o operador de multiplicação aqui, ele em sí criava o `std::vector<double>` de saída, e retornava, mas vi que isso estava fazendo meu código ficar mais lento, aí implementei duas funções:

`Matrix::buffer_multiply`, que basicamente multiplica os elementos do input, pelas linhas da matriz, e depois soma as linhas de cada coluna individualmente e isso vai para o vetor de saída, eu usei a formula `r * cols + c` para acessar um vector (no caso, o data) unidimensional como se fosse bidimensional (uma matriz de fato), isso deve ser mais rápido do que ter um vector dentro de outro vector

`Matrix::transpose_buffer_multiply`, essa sempre dá um nó na cabeça, mas ela faz basicamente a mesma coisa do buffer_multiply normal, a unica diferença é que ela usa a largura da matriz como altura, e vice-versa, e a formula para acessar o data muda para `c * cols + r`, é como se de fato eu tivesse girado a matriz, mas na verdade eu só estou acessando o data de uma forma diferente, ela é usada principalmente no backpropagate do Layer

Nesse arquivo os conceitos mais interessantes eu acho que é só isso

# Layer.hpp / Layer.cpp

Esse aqui tem coisas bem interessantes, uma parte da lerdeza do código se esconde no `Layer::backpropagate`, tanto que eu implementei o minibatch na esperança de isso de alguma forma resolver, mas não resolveu, agora ela tem 2 matrizes, uma que guarda os pesos dela em sí, e a outra que guarda as modificações que devem ser aplicadas usando o `Layer::update_weights`, o minibatch deixou ela mais lenta, mas mais pronta para futuramente implementar um multithreading, bem, não tem tantas coisas interessantes a se falar sobre o código aqui, ela e quase como uma ponte entre o NeuralNetwork e as Matrix, mas é no mínimo legal ver como as coisas se encaixam, apesar de não muito interessante ela implementa as funções mais usadas durante o treinamento e durante o uso da rede em sí, elas são:

`Layer::forward`, que basicamente multiplica as entradas pelos pesos usando o `Matrix::buffer_multiply`, e retorna isso para ou ser mostrado para o usuário, ou ser usado pelo NeuralNetwork para alimentar as proximas camadas, isso também salva qual foi a entrada e a saída para ser usado depois durante o treinamento da rede

`Layer::backpropagate`, essa aqui é a que toma boa parte do seu tempo, bem, durante o treinamento de uma com rede 2 entradas, 2 camadas ocultas, 64 neurônios cada e uma saída, com uns 5000 dados de treinamento, demora uns 40 segundos para rodar 1000 épocas no meu hardware (com a flag -O3 no compilador), desses 40 segundos uns 15 segundos são exclusivamente dessa função, por que? Não sei, mas certamente o [VerySleppy](https://github.com/VerySleepy/verysleepy) mentiu sobre algo, mas ainda assim sei que essa função não está otimizada como deveria

# NeuralNetwork.hpp / NeuralNetwork.cpp

Esse aqui controla as Layer, que controlam as Matrix, que controlam os pesos, ele pode ser inicializado com um std::vector<size_t> de acordo com a estrutura da rede que você quer, por exemplo se você quiser uma rede com 6 entradas, 32 neurônios em uma camada oculta, 16 em outra, 5 em outra, e por fim 1 saída (para quê você iria querer uma rede assim?), você pode usar ele assim:

```Cpp
NeuralNetwork neural({6, 32, 16, 5, 1});
```

Ele é bastante flexível e cuida da parte de criar layers e o `NeuralNetwork::train` dele usa o sistema de minibatch automatico, então você precisa chamar a função `NeuralNetwork::train` pelo menos `conf::BATCH_SIZE` vezes para notar alguma diferença, acho que talvez eu devesse simplificar a lógica de treinamento, para, ao invés de ter que chamar a função de `NeuralNetwork::forward_layers`, você poder simplesmente chamar a função `NeuralNetwork::train` passando um TrainingData para ela

Claro, não consegui falar muito sobre essa rede aqui, se você quiser falar sobre ela, ou estar simplesmente interessado em ter um amigo programador (que muitas vezes está ocupado trabalhando, e definitivamente não é experiente em linguagem nenhuma), você pode entrar em contado por alguma das minhas redes sociais:

Instagram (mais ativo): joel20.09
Discord (pouco ativo): \_de.v\_
E apesar de pouco usado Email: joelbergue.dev@gmail.com
