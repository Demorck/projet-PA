#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
public:
    Button(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, int width, int height, SDL_Color textColor = {255, 255, 255, 255}
            , SDL_Color buttonColor = {0, 0, 255, 255}, SDL_Color buttonHoverColor = {0, 255, 255, 255});
    Button(); 
    ~Button();
    void handleEvent(SDL_Event event);
    void render();
    bool pressed();
private:
    bool isPointInsideRect(int x, int y);

    TTF_Font* font;
    SDL_Renderer* renderer;

    int x;
    int y;
    int width;
    int height;
    
    bool isPressed;
    bool hovering;

    SDL_Color textColor;
    SDL_Color buttonColor;
    SDL_Color buttonHoverColor;

    SDL_Rect rect;
    std::string text;
    SDL_Texture* textTexture;
    SDL_Surface* surface;
};

#endif