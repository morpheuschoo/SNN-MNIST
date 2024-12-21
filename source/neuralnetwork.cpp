#include "neuralnetwork.hpp"

NeuralNetwork::NeuralNetwork() {}

void NeuralNetwork::ShuffleAll() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(shuffleIndex.begin(), shuffleIndex.end(), std::default_random_engine(seed));
}

bool NeuralNetwork::InitTrainIO(const std::string &trainFilePath, const std::string &testFilePath) {
    if(!parser.LoadTrainAndTest(trainFilePath, testFilePath)) {
        return false;
    }

    parser.LinkTrainAndTest(trainInputs, trainOutputs, testInputs, testOutputs);

    NUMTRAININGSETS = trainOutputs->size();
    NUMTESTSETS = testOutputs->size();

    for(size_t i = 0; i < NUMTRAININGSETS; i++) {
        shuffleIndex.push_back(i);
    }

    return true;
}

bool NeuralNetwork::InitNodes(const std::vector<size_t> &numNodes) {
    NUMLAYERS = numNodes.size() - 1;

    if(NUMLAYERS < 1) {
        return false;
    }

    // populate allLayers with Layers
    for(size_t i = 0; i < NUMLAYERS; i++) {
        allLayers.push_back(Layer(numNodes[i], numNodes[i + 1]));
    }

    // link inputNodes of layers together
    for(size_t i = 1; i < NUMLAYERS; i++) {
        allLayers[i].LinkInput(allLayers[i - 1].activatedOutputNodes);
    }

    return true;
}

std::vector<double>& NeuralNetwork::ForwardPass(const std::vector<double> &input) {
    allLayers[0].LinkInput(input);

    for(auto &layer : allLayers) {
        layer.ForwardPass();
    }

    return allLayers.back().activatedOutputNodes;
}

void NeuralNetwork::BackPropagation(const std::vector<double> &expectedOutput) {
    allLayers.back().OutputBackPropagation(expectedOutput);
    for(size_t i = NUMLAYERS - 2; i != -1; i--) {
        allLayers[i].HiddenBackPropagation(allLayers[i + 1]);
    }
}

void NeuralNetwork::UpdateWeightAndBiases(double batchSize) {
    for(auto &layer : allLayers) {
        layer.PerformGradientDescent(LR, batchSize);
    }
}

void NeuralNetwork::Train(const size_t NUMEPOCHS) { 
    size_t numInBatch = 0;
    for(size_t _ = 0; _ < NUMEPOCHS; _++) {
        ShuffleAll();
        for(size_t i = 0; i < NUMTRAININGSETS; i++) {
            ForwardPass((*trainInputs)[shuffleIndex[i]]);

            // backpropagation (update deltaWeights and deltaBias)
            BackPropagation((*trainOutputs)[shuffleIndex[i]]);
            numInBatch++;

            // update weights and biases after every batch
            if(numInBatch == BATCHSIZE || i == NUMTRAININGSETS - 1) {
                UpdateWeightAndBiases(numInBatch);
                numInBatch = 0;
            }
        }
        Test(false);
    }
    Test(true);
}

void NeuralNetwork::Test(bool isFinal) {
    size_t totalCorrect = 0;
    double totalCost = 0;

    for(size_t testNo = 0; testNo < NUMTESTSETS; testNo++) {
        std::vector<double> &actualOutput = ForwardPass((*testInputs)[testNo]);
        if(IsMyOutputCorrect(actualOutput, (*testOutputs)[testNo])) {
            totalCorrect++;
        }
        totalCost += allLayers.back().Cost((*testOutputs)[testNo]);

        if(isFinal) {
            std::cout << "\n";
            std::cout << DisplayInput((*testInputs)[testNo]) << "\n";
            std::cout << "EXPECTED OUTPUT: " << ObtainOutputValue((*testOutputs)[testNo]) << " ";
            std::cout << "ACTUAL OUTPUT: " << ObtainOutputValue(actualOutput) << "\n";
        }
    }

    std::cout << "ACCURACY: " << (double)totalCorrect / (double)NUMTESTSETS * 100 << "% ";
    std::cout << "AVERAGE COST: " << totalCost / NUMTESTSETS << std::endl;
}

size_t NeuralNetwork::ObtainOutputValue(const std::vector<double> &output) {
    size_t MAXSIZE = output.size();
    double maxValue = 0;
    size_t maxIndex = 0;
    
    for(size_t i = 0; i < MAXSIZE; i++) {
        if(maxValue < output[i]) {
            maxValue = output[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

bool NeuralNetwork::IsMyOutputCorrect(const std::vector<double> &actualOutput, const std::vector<double> &expectedOutput) {
    size_t maxIndex = ObtainOutputValue(actualOutput);

    if(expectedOutput[maxIndex] == 1) {
        return true;
    } else {
        return false;
    }
}

std::string NeuralNetwork::DisplayInput(const std::vector<double> &input) {
    std::string display = "";
    for(size_t i = 0; i < 28; i++) {
        for(size_t j = 0; j < 28; j++) {
            display += (input[i * 28 + j] != 0 ? "1" : "-");
            display += " ";
        }
        display += "\n";
    }
    return display;
}