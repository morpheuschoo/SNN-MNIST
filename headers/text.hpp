#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text {
private:
    static std::map<std::string, TTF_Font*> mapFonts;

    SDL_Renderer *renderer;
    SDL_Rect textRect;
    SDL_Texture *textTexture;

public:
    Text(SDL_Renderer *renderer);

    static bool LoadFont(const std::string &fontName, int fontSize);
    bool WriteText(const std::string &text, SDL_Color color, const std::string &fontName, int fontSize);    
    void SetPosition(int x, int y);
    void Render();
    static void CloseFonts();
    void CloseTexture();
};

#endif