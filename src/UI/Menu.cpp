#include <UI/Menu.hpp>
#include <iostream>

const SDL_Color BACKGROUND_COLOR = { 255, 255, 255, 255 };

Menu::Menu(SDL_Renderer* renderer, int width, int height)
    : renderer(renderer), width(width), height(height)
{
    loadFont();
    loadButtons();
    std::string font = "assets/Roboto-Regular.ttf";
    std::string titleText = "Le jeu de dingue";

    title = new Text(renderer, font, titleText, (width + 100) / 3, 30, 60, 20, {255, 255, 255, 255});
}

Menu::~Menu()
{
    if(titleTexture != nullptr)
        SDL_DestroyTexture(titleTexture);
        
    for (int i = 0; i < 3; i++)
    {
        delete buttons[i];
    }
}

/**
 * 
 * ! Penser à modifier exit pour que ce soit smooth
*/
void Menu::update(float deltaTime, State& state)
{
    if (buttons[0]->pressed())
    {
        state = Continue;
    }

    if (buttons[1]->pressed())
    {
        state = NewGame;
    }

    if (buttons[2]->pressed())
    {
        state = Settings;
    }

    if (buttons[3]->pressed())
    {
        state = Exit;
    }
}

void Menu::render(bool canContinue)
{
    title->render();
    
    for (int i = 0; i < sizeof(buttons) / sizeof(Button*); i++) {
        if (i == 0 && canContinue)
        {
            buttons[i]->render();
        }
        if (i != 0)
        {
            buttons[i]->render();
        }
    }
}

void Menu::handleEvents(SDL_Event e)
{
    for (int i = 0; i < sizeof(buttons) / sizeof(Button*); i++)
    {
        buttons[i]->handleEvent(e);
    }
}

void Menu::clearMenu()
{
    for (int i = 0; i < sizeof(buttons) / sizeof(Button*); i++)
    {
        delete buttons[i];
    }
    SDL_DestroyTexture(titleTexture);
}

void Menu::loadFont()
{
    font = TTF_OpenFont("assets/Roboto-Regular.ttf", 32);
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont error: " << TTF_GetError() << std::endl;
        exit(1);
    }
}

void Menu::loadButtons()
{
    std::string texts[4] = {"Continue", "New Game", "Settings", "Exit"};
    for (int i = 0; i < sizeof(buttons) / sizeof(Button*); ++i) {
        buttons[i] = new Button(renderer, font, texts[i], 50, 200 + i*50, 300, 40);
    }
}

void Menu::handleMouseClick(int x, int y)
{
        
}

void Menu::handleTextInput(char* text)
{

}