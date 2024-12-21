#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <random>

class Layer {
private:
    size_t NUMINPUTNODES;
    size_t NUMOUTPUTNODES;

    const std::vector<double> *inputNodes;

    std::vector<std::vector<double>> weights;
    std::vector<double> bias;

    std::vector<double> unactivatedOutputNodes;

    std::vector<double> commonDerivative;
    std::vector<std::vector<double>> deltaWeights;
    std::vector<double> deltaBias;

    void InitWeightsAndBias();

    double Sigmoid(double input);
    double DSigmoid(double input);

    double Cost(double expectedOutput, double actualOutput);
    double DCost(double expectedOutput, double actualOutput);

public:
    std::vector<double> activatedOutputNodes;

    Layer();
    Layer(size_t NUMINPUTNODES, size_t NUMOUTPUTNODES);
    void LinkInput(const std::vector<double> &beforeInput);

    void ForwardPass();

    void OutputBackPropagation(const std::vector<double> &expectedOutputs);
    void HiddenBackPropagation(const Layer &layerInFront);
    void PerformGradientDescent(double learningRate, size_t batchSize);

    double Cost(const std::vector<double> &expectedOutput);
};

#endif