#include "window.hpp"

Window::Window() {
    window = nullptr;
    renderer = nullptr;
}

bool Window::Init() {
    if(SDL_Init(SDL_INIT_VIDEO < 0)) {
        std::cout << "SDL could not initialise: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Simple Neural Network", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr) {
        std::cout << "Window could not be created: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr) {
        std::cout << "Renderer could not be created: " << SDL_GetError() << std::endl;
        return false;
    }

    if(!text.LoadFont("arial", 50)) {
        return false;
    }

    text.LinkRenderer(renderer);
    text.WriteText("HELLO", SDL_Color{255, 255, 255}, "arial", 50);
    text.SetPosition(100, 100);

    return true;
}

void Window::Run() {
    SDL_Event e;
    bool RUNNING = true;
    while(RUNNING) {
        // poll for events
        if(SDL_WaitEvent(&e)) {
            if(e.type == SDL_QUIT) {
                RUNNING = false;
            }
        }

        // set background to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // draw
        text.Render();
        
        // display drawing
        SDL_RenderPresent(renderer);
    }
}

void Window::Close() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    text.Close();
}