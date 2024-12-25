#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "text.hpp"

class Window{
private:
    constexpr static int WINDOW_WIDTH = 800;
    constexpr static int WINDOW_HEIGHT = 600;

    SDL_Window *window;
    SDL_Renderer *renderer;

    Text text;

public:
    Window();

    bool Init();
    void Run();
    void Close();

};

#endif