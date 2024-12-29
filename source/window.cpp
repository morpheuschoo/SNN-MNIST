#include "window.hpp"

Window::Window() : numberDisplay(renderer, WINDOW_WIDTH / 2 - 14 * pixelSize, WINDOW_HEIGHT / 2 - 14 * pixelSize, pixelSize) {
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

    if(TTF_Init() < 0) {
        std::cout << "SDL_TTF could not initialise: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

void Window::RunSNN() {
    NN.InitTrainIO("assets/data/small_mnist_train.csv", "assets/data/small_mnist_test.csv");
    NN.InitNodes({784, 100, 10});
    NN.Train(1);
    numberDisplay.PairNeuralNetworkVariables(NN);
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
            if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_RIGHT) {
                    numberDisplay.Increment();
                }
                if(e.key.keysym.sym == SDLK_LEFT) {
                    numberDisplay.Decrement();
                }
            }
        }

        // set background to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // draw
        numberDisplay.Render();

        // display drawing
        SDL_RenderPresent(renderer);
    }
}

void Window::Close() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    numberDisplay.Close();
    Text::CloseFonts();
    TTF_Quit();
}