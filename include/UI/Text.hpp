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
    void render(bool clear = 0);
    void setText(const std::string& newText);
    std::string getText();
    
private:
    void loadFont();

    int x;
    int y;
    int width;
    int height;

    TTF_Font* font;
    std::string fontPath;
    SDL_Renderer* renderer;
    std::string text;
    SDL_Texture* textTexture;
    SDL_Surface* surface;
    SDL_Color color;
};

#endif