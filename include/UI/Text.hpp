#ifndef TEXT_HPP
#define TEXT_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text {
public:
    Text(SDL_Renderer* renderer, std::string fontPath, std::string text, int x, int y, int width, int height, SDL_Color color); 
    Text(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color); 
    Text();
    ~Text();
    void render();
    void setText(const std::string& newText);
    std::string getText();
    
private:
    void loadFont(int height);
    SDL_Renderer* renderer = nullptr;
    std::string fontPath;
    std::string text;

    int x;
    int y;
    int width;
    int height;
    
    SDL_Color color;


    TTF_Font* font = nullptr;
    SDL_Texture* textTexture = nullptr;
};

#endif