#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include "neuralnetwork.hpp"
#include "numberdisplay.hpp"

class Window{
private:
    constexpr static int WINDOW_WIDTH = 1000;
    constexpr static int WINDOW_HEIGHT = 1000;
    constexpr static int pixelSize = 20;

    SDL_Window *window;
    SDL_Renderer *renderer;

    NeuralNetwork NN;

    NumberDisplay numberDisplay;

public:
    Window();

    bool Init();
    void Run();
    void Close();

    void RunSNN();

};

#endif