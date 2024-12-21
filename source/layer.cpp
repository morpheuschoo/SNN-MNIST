#include "layer.hpp"

Layer::Layer() {}

Layer::Layer(size_t NUMINPUTNODES, size_t NUMOUTPUTNODES) {
    this->NUMINPUTNODES = NUMINPUTNODES;
    this->NUMOUTPUTNODES = NUMOUTPUTNODES;

    weights.resize(NUMINPUTNODES, std::vector<double>(NUMOUTPUTNODES, 0));
    bias.resize(NUMOUTPUTNODES, 0);
    
    commonDerivative.resize(NUMOUTPUTNODES, 0);
    deltaWeights.resize(NUMINPUTNODES, std::vector<double>(NUMOUTPUTNODES, 0));
    deltaBias.resize(NUMOUTPUTNODES, 0);

    InitWeightsAndBias();

    unactivatedOutputNodes.resize(NUMOUTPUTNODES, 0);
    activatedOutputNodes.resize(NUMOUTPUTNODES, 0);

    inputNodes = NULL;
}

double Layer::Sigmoid(double input) {
    return 1 / (1 + exp(-input));
}

double Layer::DSigmoid(double input) {
    return Sigmoid(input) * (1 - Sigmoid(input));
}

double Layer::Cost(double expectedOutput, double actualOutput) {
    return (actualOutput - expectedOutput) * (actualOutput - expectedOutput);
}

double Layer::DCost(double expectedOutput, double actualOutput) {
    return 2 * (actualOutput - expectedOutput);
}

void Layer::InitWeightsAndBias() {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(-1, 1);

    // initialise weights
    for(auto &i : weights) {
        for(auto &v : i) {
            v = distribution(generator);
        }
    }

    // initialise bias
    for(auto &v : bias) {
        v = distribution(generator);
    }
}

void Layer::LinkInput(const std::vector<double> &beforeInput) {
    inputNodes = &beforeInput;
}

void Layer::ForwardPass() {
    for(size_t outputNo = 0; outputNo < NUMOUTPUTNODES; outputNo++) {
        unactivatedOutputNodes[outputNo] = bias[outputNo];
        for(size_t inputNo = 0; inputNo < NUMINPUTNODES; inputNo++) {
            unactivatedOutputNodes[outputNo] += weights[inputNo][outputNo] * (*inputNodes)[inputNo];
        }
        activatedOutputNodes[outputNo] = Sigmoid(unactivatedOutputNodes[outputNo]);
    }
}

void Layer::OutputBackPropagation(const std::vector<double> &expectedOutputs) {
    for(size_t outputNo = 0; outputNo < NUMOUTPUTNODES; outputNo++) {
        commonDerivative[outputNo] = DCost(expectedOutputs[outputNo], activatedOutputNodes[outputNo]) * DSigmoid(unactivatedOutputNodes[outputNo]);
        deltaBias[outputNo] += commonDerivative[outputNo] * 1;
        for(size_t inputNo = 0; inputNo < NUMINPUTNODES; inputNo++) {
            deltaWeights[inputNo][outputNo] += commonDerivative[outputNo] * (*inputNodes)[inputNo];
        }
    }
}

void Layer::HiddenBackPropagation(const Layer &layerInFront) {
    for(size_t outputNo = 0; outputNo < NUMOUTPUTNODES; outputNo++) {
        commonDerivative[outputNo] = 0;
        for(size_t frontOutputNo = 0; frontOutputNo < layerInFront.NUMOUTPUTNODES; frontOutputNo++) {
            commonDerivative[outputNo] += layerInFront.commonDerivative[frontOutputNo] * layerInFront.weights[outputNo][frontOutputNo];
        }
        commonDerivative[outputNo] *= DSigmoid(unactivatedOutputNodes[outputNo]);
        deltaBias[outputNo] += commonDerivative[outputNo] * 1;
        for(size_t inputNo = 0; inputNo < NUMINPUTNODES; inputNo++) {
            deltaWeights[inputNo][outputNo] += commonDerivative[outputNo] * (*inputNodes)[inputNo];
        }
    }
}

void Layer::PerformGradientDescent(double learningRate, size_t batchSize) {
    // find average
    for(size_t outputNo = 0; outputNo < NUMOUTPUTNODES; outputNo++) {
        deltaBias[outputNo] /= (double)batchSize;
        for(size_t inputNo = 0; inputNo < NUMINPUTNODES; inputNo++) {
            deltaWeights[inputNo][outputNo] /= (double)batchSize;
        }
    }

    // change weights and biases
    for(size_t outputNo = 0; outputNo < NUMOUTPUTNODES; outputNo++) {
        bias[outputNo] -= deltaBias[outputNo] * learningRate;
        for(size_t inputNo = 0; inputNo < NUMINPUTNODES; inputNo++) {
            weights[inputNo][outputNo] -= deltaWeights[inputNo][outputNo] * learningRate;
        }
    }

    // reset deltaWeights and deltaBias to 0
    for(auto &i : deltaWeights) {
        for(auto &v : i) {
            v = 0;
        }
    }
    
    for(auto &v : deltaBias) {
        v = 0;
    }
}

double Layer::Cost(const std::vector<double> &expectedOutput) {
    double totalCost = 0;
    for(size_t i = 0; i < NUMOUTPUTNODES; i++) {
        totalCost += Cost(expectedOutput[i], activatedOutputNodes[i]);
    }

    return sqrt(totalCost / NUMOUTPUTNODES);
}