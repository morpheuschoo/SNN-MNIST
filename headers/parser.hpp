#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>

class Parser {
private:
    std::vector<std::vector<double>> trainInput;
    std::vector<std::vector<double>> trainOutput;

    std::vector<std::vector<double>> testInput;
    std::vector<std::vector<double>> testOutput;

    bool OpenFile(const std::string &filePath, std::vector<std::vector<double>> &input, std::vector<std::vector<double>> &output);

public:
    Parser();

    bool LoadTrainAndTest(const std::string &trainFilePath, const std::string &testFilePath);
    void LinkTrainAndTest(
        const std::vector<std::vector<double>> *&trainInput, 
        const std::vector<std::vector<double>> *&trainOutput, 
        const std::vector<std::vector<double>> *&testInput, 
        const std::vector<std::vector<double>> *&testOutput
    );
};

#endif