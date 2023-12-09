#include <UI/Menu.hpp>
#include <iostream>

/**
 * @param renderer : Le renderer pour le menu
 * @param width : La largeur du menu
 * @param height : La hauteur du menu
*/
Menu::Menu(SDL_Renderer* renderer, int width, int height)
    : renderer(renderer), width(width), height(height)
{
    loadFont();
    loadButtons();
    std::string font = "assets/Roboto-Regular.ttf";
    std::string titleText = "Le jeu de dingue";

    title = new Text(renderer, font, titleText, width / 2 - 145, 30, 150, 45, {255, 255, 255, 255});
}

/**
 * @brief Détruit la texture du titre + chaque bouton
*/
Menu::~Menu()
{
    delete title;
    TTF_CloseFont(font);
        
    for (int i = 0; i < NB_BOUTON_MENU - 1; i++)
    {
        delete buttons[i];
    }
}

/**
 * Modifie l'état du  jeu en fonction de quel bouton on clique
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
        state = Exit;
    }
}

/**
 * @param canContinue Utilisé si le jeu peut continuer (pour afficher ou non le bouton correspondant)
 * 
 * @brief Affiche le titre + les boutons
*/
void Menu::render(bool canContinue)
{
    title->render();
    
    for (int i = 0; i < NB_BOUTON_MENU; i++) {
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

/**
 * @param e l'event en cours
 * @brief Gère les événements de chaque bouton
*/
void Menu::handleEvents(SDL_Event e)
{
    for (int i = 0; i < NB_BOUTON_MENU; i++)
    {
        buttons[i]->handleEvent(e);
    }
}

/**
 * @brief Charge la police pour le menu
*/
void Menu::loadFont()
{
    font = TTF_OpenFont("assets/Roboto-Regular.ttf", 32);
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont error: " << TTF_GetError() << std::endl;
        exit(1);
    }
}

/**
 * @brief Charge chaque bouton du menu
*/
void Menu::loadButtons()
{
    std::string texts[3] = {"Continue", "New Game", "Exit"};
    for (int i = 0; i < NB_BOUTON_MENU; ++i) {
        buttons[i] = new Button(renderer, font, texts[i], 50, 200 + i*50, 300, 40);
    }
}