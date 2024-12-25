#include "neuralnetwork.hpp"
#include "window.hpp"

int main(int argc, char *argv[]) {
    Window w;

    if(!w.Init()) {
        return -1;
    }

    w.Run();

    w.Close();
    
    // NeuralNetwork NN;

    // if(!NN.InitTrainIO("datasets/small_mnist_train.csv", "datasets/small_mnist_test.csv")) {
    //     return -1;
    // }

    // NN.InitNodes({784, 100, 10});
    
    // NN.Train(3);

    return 0;
}