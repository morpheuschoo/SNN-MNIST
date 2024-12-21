#include <SDL2/SDL.h>
#include <iostream>

class Window{
private:
    constexpr static int WINDOW_WIDTH = 1000;
    constexpr static int WINDOW_HEIGHT = 1000;

    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    Window();

    bool Init();
    void EventLoop();
    void Close();

};