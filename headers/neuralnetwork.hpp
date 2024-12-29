#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "parser.hpp"
#include "layer.hpp"

class NeuralNetwork {
private:
    static constexpr double LR = 0.5;
    static constexpr double BATCHSIZE = 32;

    Parser parser;

    const std::vector<std::vector<double>>* trainInputs;
    const std::vector<std::vector<double>>* trainOutputs;
    const std::vector<std::vector<double>>* testInputs;
    const std::vector<std::vector<double>>* testOutputs;
    std::vector<size_t> shuffleIndex;
    size_t NUMTRAININGSETS;
    size_t NUMTESTSETS;

    std::vector<size_t> processedTestExpectedOutputs;
    std::vector<size_t> processedTestActualOutputs;

    std::vector<Layer> allLayers;
    size_t NUMLAYERS;

    void ShuffleAll();
    std::vector<double>& ForwardPass(const std::vector<double> &input);
    void BackPropagation(const std::vector<double> &expectedOutput);
    void UpdateWeightAndBiases(double batchSize);

    size_t ObtainOutputValue(const std::vector<double> &output);
    bool IsMyOutputCorrect(const std::vector<double> &actualOutput, const std::vector<double> &expectedOutput);

    void Test(bool isFinal);

    std::string DisplayInput(const std::vector<double> &input);

public:
    NeuralNetwork();
    bool InitTrainIO(const std::string &trainFilePath, const std::string &testFilePath);
    bool InitNodes(const std::vector<size_t> &numNodes);

    void Train(const size_t NUMEPOCHS);

    void PairVariables(
        const std::vector<std::vector<double>> *&testInputs,
        const std::vector<size_t> *&processedTestExpectedOutputs,
        const std::vector<size_t> *&processedTestActualOutputs,
        size_t &NUMTESTSETS
    );
    
};

#endif