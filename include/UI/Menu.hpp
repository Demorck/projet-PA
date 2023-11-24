#ifndef MENU_HPP
#define MENU_HPP
#include <UI/Button.hpp>
#include <UI/Text.hpp>
#include <Helpers/Enums.hpp>


class Menu
{
    public:
        Menu(SDL_Renderer* renderer, int width, int height);
        Menu();
        ~Menu();

        void update(float deltaTime, State& state);
        void render();
        void handleEvents(SDL_Event e);

    private:
        void handleMouseClick(int x, int y);
        void handleTextInput(char* text);
        void loadFont();
        void loadButtons();
        void clearMenu();
        
        
        SDL_Renderer* renderer;
        TTF_Font* font;
        std::string fontPath;

        Text* title;
        SDL_Texture* titleTexture;

        int width;
        int height;

        SDL_Color textColor;
        SDL_Rect textRect;

        Button* buttons[3];
};

#endif