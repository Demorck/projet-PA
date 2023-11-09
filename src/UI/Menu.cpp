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

    title = new Text(renderer, font, titleText, (width + 100) / 2, 30, 60, 20, {255, 255, 255, 255});
}

Menu::~Menu()
{
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(inputTexture);
}

/**
 * 
 * ! Penser à modifier exit pour que ce soit smooth
*/
void Menu::update(float deltaTime)
{
    if (buttons[0]->pressed())
    {
        this->clearMenu();
    }

    if (buttons[1]->pressed())
    {
        this->clearMenu();
    }

    if (buttons[2]->pressed())
    {
        exit(0);
    }
}

void Menu::render()
{
    title->render();

    for (int i = 0; i < sizeof(buttons) / sizeof(Button*); i++) {
        buttons[i]->render();
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
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(inputTexture);
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
    std::string texts[3] = {"New Game", "Settings", "Exit"};
    for (int i = 0; i < 3; ++i) {
        buttons[i] = new Button(renderer, font, texts[i], 50, 200 + i*50, 300, 40);
    }
}

void Menu::handleMouseClick(int x, int y)
{
        
}

void Menu::handleTextInput(char* text)
{

}