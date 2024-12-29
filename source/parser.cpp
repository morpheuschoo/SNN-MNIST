#include "parser.hpp"

Parser::Parser() {}

bool Parser::OpenFile(const std::string &filePath, std::vector<std::vector<double>> &input, std::vector<std::vector<double>> &output) {
    std::ifstream file;
    std::string line;
    std::string value;

    size_t currIndex = 0;

    file.open(filePath);

    if(!file.is_open()) {
        return false;
    }

    // skip header line
    std::getline(file, line);
    
    while(std::getline(file, line)) {
        std::istringstream lineStream(line);
        
        input.push_back(std::vector<double>{});

        // obtain expected output from CSV
        std::getline(lineStream, value, ',');
        std::vector<double> vPush(10, 0);
        vPush[stoi(value)] = 1;
        output.push_back(vPush);

        // obtain input from CSV
        while(std::getline(lineStream, value, ',')) {
            input[currIndex].push_back(std::stod(value) / 255);
        }
        
        ++currIndex;
    }
    
    file.close();

    return true;
}

bool Parser::LoadTrainAndTest(const std::string &trainFilePath, const std::string &testFilePath) {
    if(!OpenFile(trainFilePath, trainInput, trainOutput)) {
        std::cout << "Unable to open: " << trainFilePath << std::endl;
        return false;
    }
    if(!OpenFile(testFilePath, testInput, testOutput)) {
        std::cout << "Unable to open: " << testFilePath << std::endl;
        return false;
    }
    return true;
}

void Parser::LinkTrainAndTest(
    const std::vector<std::vector<double>> *&trainInput, 
    const std::vector<std::vector<double>> *&trainOutput, 
    const std::vector<std::vector<double>> *&testInput, 
    const std::vector<std::vector<double>> *&testOutput) {
    trainInput  = &(this->trainInput);
    trainOutput = &(this->trainOutput);
    testInput   = &(this->testInput);
    testOutput  = &(this->testOutput);
}