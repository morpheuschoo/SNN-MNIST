#include "text.hpp"

std::map<std::string, TTF_Font*> Text::mapFonts;
bool Text::TTF_INIT = false;
bool Text::TTF_DESTROYED = false;

Text::Text() : textRect{0, 0, 0, 0} {
    // Ensures that TTF_Init runs once
    if(!TTF_INIT) {
        if(TTF_Init() < 0) {
            std::cout << "SDL_ttf could not initialise: " << TTF_GetError() << std::endl;
        }
        TTF_INIT = true;
    }

    renderer = nullptr;
    textTexture = nullptr;
}

bool Text::LoadFont(const std::string &fontName, int fontSize) {
    TTF_Font *font = nullptr;
    font = TTF_OpenFont((std::string("assets/fonts/") + fontName + std::string(".ttf")).c_str(), fontSize);
    if(font == nullptr) {
        std::cout << "Unable to open font: " << TTF_GetError() << std::endl;
        return false;
    }
    mapFonts[fontName + std::to_string(fontSize)] = font;
    
    for(const auto &i : mapFonts) {
        std::cout << i.first << " " << i.second << std::endl;
    }
    
    return true;
}

void Text::LinkRenderer(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

bool Text::WriteText(const std::string &text, SDL_Color color, const std::string &fontName, int fontSize) {
    std::string mapIndex = fontName + std::to_string(fontSize);
    if(mapFonts.find(mapIndex) == mapFonts.end()) {
        std::cout << "Font " << fontName << " of size " << fontSize << " does not exist!" << std::endl;
        std::cout << "Load the font in using LoadFont first!" << std::endl;
        return false;
    }
    
    SDL_Surface *tempSurface = nullptr;
    tempSurface = TTF_RenderText_Solid(mapFonts[mapIndex], text.c_str(), color);
    
    textRect.w = tempSurface->w;
    textRect.h = tempSurface->h;
    textTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    
    if(textTexture == nullptr) {
        std::cout << "Unable to create text surface: " << SDL_GetError() << std::endl;
        return false;
    }
    
    SDL_FreeSurface(tempSurface);
    
    return true;
}

void Text::SetPosition(int x, int y) {
    textRect.x = x;
    textRect.y = y;
}

void Text::Render() {
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

void Text::Close() {
    SDL_DestroyTexture(textTexture);
    if(!TTF_DESTROYED) {
        for(auto &i : mapFonts) {
            TTF_CloseFont(i.second);
        }
        TTF_Quit();
    }
}