#ifndef NUMBERDISPLAY_H
#define NUMBERDISPLAY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "text.hpp"
#include "neuralnetwork.hpp"

class NumberDisplay {
private:
    size_t index;
    size_t NUMTESTSETS;
    SDL_Renderer *&renderer;

    std::vector<SDL_Rect> numberRects;
    SDL_Rect borderRect;

    const std::vector<std::vector<double>> *testInputs;
    const std::vector<size_t> *processedTestExpectedOutputs;
    const std::vector<size_t> *processedTestActualOutputs;

    std::vector<Text> tTestExpectedOutputs;
    std::vector<Text> tTestActualOutputs;

public:
    NumberDisplay(SDL_Renderer *&_renderer, int x, int y, int pixelSize);

    void PairNeuralNetworkVariables(NeuralNetwork &NN);
    void Render();

    void Increment();
    void Decrement();

    void Close();

};

#endif