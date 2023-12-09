#ifndef MENU_HPP
#define MENU_HPP
#include <UI/Button.hpp>
#include <UI/Text.hpp>
#include <Helpers/Enums.hpp>
#include <Constant.hpp>


class Menu
{
    public:
        Menu(SDL_Renderer* renderer, int width, int height);
        Menu();
        ~Menu();

        void update(float deltaTime, State& state);
        void render(bool canContinue);
        void handleEvents(SDL_Event e);

    private:
        void loadFont();
        void loadButtons();
        
        
        SDL_Renderer* renderer;
        TTF_Font* font;
        std::string fontPath;

        Text* title;

        int width;
        int height;

        SDL_Color textColor;
        SDL_Rect textRect;

        Button* buttons[NB_BOUTON_MENU];
};

#endif