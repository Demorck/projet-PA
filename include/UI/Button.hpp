#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <Constant.hpp>

class Button {
public:
    Button(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, int width, int height, SDL_Color textColor = {255, 255, 255, 255}
            , SDL_Color buttonColor = COUL_BOUT_DEFAULT, SDL_Color buttonHoverColor = {0, 255, 255, 255});
    Button(); 
    ~Button();
    void handleEvent(SDL_Event event);
    void render();
    bool pressed();
private:
    bool isPointInsideRect(int x, int y);


    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string text;

    int x;
    int y;
    int width;
    int height;

    SDL_Color textColor;
    SDL_Color buttonColor;
    SDL_Color buttonHoverColor;

    
    bool isPressed;
    bool hovering;

    SDL_Rect rect;
    SDL_Texture* textTexture;
    SDL_Surface* surface;
};

#endif