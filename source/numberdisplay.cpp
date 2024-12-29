#include "numberdisplay.hpp"

NumberDisplay::NumberDisplay(SDL_Renderer *&_renderer, int x, int y, int pixelSize) : renderer(_renderer) {
    index = 0;

    // 28 x 28 display
    int currX = x;
    int currY = y;
    for(size_t i = 0; i < 28; i++) {
        currX = x;
        for(size_t j = 0; j < 28; j++) {
            numberRects.push_back(SDL_Rect{currX, currY, pixelSize, pixelSize});
            currX += pixelSize;
        }
        currY += pixelSize;
    }

    // border
    borderRect = SDL_Rect{x, y, 28 * pixelSize + 5, 28 * pixelSize + 5};
}

void NumberDisplay::PairNeuralNetworkVariables(NeuralNetwork &NN) {
    // pair variables
    NN.PairVariables(testInputs, processedTestExpectedOutputs, processedTestActualOutputs, NUMTESTSETS);

    if(!Text::LoadFont("arial", 30)) {
        return;
    }

    for(size_t i = 0; i < NUMTESTSETS; i++) {
        tTestActualOutputs.push_back(Text(renderer));
        tTestActualOutputs.back().WriteText(
            "Predicted: " + std::to_string((*processedTestActualOutputs)[i]),
            SDL_Color{255, 255, 255},
            "arial",
            30
        );
        tTestActualOutputs.back().SetPosition(30, 30);
        
        tTestExpectedOutputs.push_back(Text(renderer));
        tTestExpectedOutputs.back().WriteText(
            "Expected: " + std::to_string((*processedTestExpectedOutputs)[i]),
            SDL_Color{255, 255, 255},
            "arial",
            30
        );
        tTestExpectedOutputs.back().SetPosition(30, 80);
    }
}

void NumberDisplay::Render() {
    tTestActualOutputs[index].Render();
    tTestExpectedOutputs[index].Render();

    for(size_t i = 0; i < 784; i++) {
        double color = (*testInputs)[index][i] * 255;
        SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &numberRects[i]);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &borderRect);

}

void NumberDisplay::Increment() {
    if(++index == NUMTESTSETS) {
        index = 0;
    }
}

void NumberDisplay::Decrement() {
    if(--index == -1) {
        index = NUMTESTSETS - 1;
    }
}

void NumberDisplay::Close() {
    for(size_t i = 0; i < NUMTESTSETS; i++) {
        tTestActualOutputs[i].CloseTexture();
        tTestActualOutputs[i].CloseTexture();
    }
}