#ifndef MENU_HPP
#define MENU_HPP
#include <UI/Button.hpp>
#include <UI/Text.hpp>

class Menu
{
    public:
        Menu(SDL_Renderer* renderer, int width, int height);
        Menu();
        ~Menu();

        void update(float deltaTime);
        void render();

    private:
        void handleMouseClick(int x, int y);
        void handleTextInput(char* text);
        void loadFont();
        void loadButtons();
        void clearMenu();
        
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
        std::string fontPath;

        Text* title;
        SDL_Texture* titleTexture;
        
        SDL_Texture* inputTextTexture;
        SDL_Texture* bubbleSortTexture;
        SDL_Texture* bubbleSortTextTexture;

        int width;
        int height;

        SDL_Color textColor;
        SDL_Rect textRect;

        SDL_Texture* textTexture;
        std::string inputString;

        SDL_Rect inputRect;
        SDL_Texture* inputTexture;

        Button* buttons[3];
};

#endif