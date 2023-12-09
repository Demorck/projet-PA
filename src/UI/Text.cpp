#include <UI/Text.hpp>
#include <iostream>

/**
 * @param renderer : Le renderer pour afficher le texte
 * @param fontPath : Le chemin pour la police du texte
 * @param text : Le texte à afficher
 * @param x : La position en abscisse du texte
 * @param y : la position en ordonnée du texte
 * @param width : la largeur du texte
 * @param height : la hauteur du texte
 * @param color : la couleur du texte
*/
Text::Text(SDL_Renderer* renderer, std::string fontPath, std::string text, int x, int y, int width, int height, SDL_Color color)
    : renderer(renderer), fontPath(fontPath), text(text), x(x), y(y), width(width), height(height), color(color)
{

    loadFont();
    TTF_SetFontSize(font, height);

    // Créer la surface
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surface == nullptr) {
        throw std::runtime_error("Failed to create surface: " + std::string(TTF_GetError()));
    }

    // Créer la texture à partir de la surface
    textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (textTexture == NULL) {
        std::cerr << "SDL_CreateTextureFromSurface Text: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_FreeSurface(surface);
}

/**
 * @param renderer : Le renderer pour afficher le texte
 * @param x : La position en abscisse du texte
 * @param y : la position en ordonnée du texte
 * @param width : la largeur du texte
 * @param height : la hauteur du texte
 * @param color : la couleur du texte
 * 
 * @brief Ce constructeur utilise une police par défaut et un texte par défaut
*/
Text::Text(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color)
    : renderer(renderer), x(x), y(y), width(width), height(height), color(color)
{

    fontPath = "assets/Roboto-Regular.ttf";
    text = "Lorem Ipsum";

    loadFont();

    // Créer la surface
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surface == nullptr) {
        throw std::runtime_error("Failed to create surface: " + std::string(TTF_GetError()));
    }

    // Créer la texture à partir de la surface
    textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (textTexture == NULL) {
        std::cerr << "SDL_CreateTextureFromSurface Text: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_FreeSurface(surface);
}

/**
 * @brief Ferme la police et détruit la texture
*/
Text::~Text()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTexture);
}

/**
 * @brief Affiche le texte à l'endroit voulu
*/
void Text::render()
{
    SDL_Rect textRect = { x, y, width, height };
    if (SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h) != 0) {
        std::cerr << "SDL_QueryTexture Text: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    // textRect.x -= textRect.w / 2;
    // textRect.y -= textRect.h / 2; 
    if (SDL_RenderCopy(renderer, textTexture, NULL, &textRect) != 0) {
        std::cerr << "SDL_RenderCopy Text: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
}

/**
 * @param newText : Le nouveau texte à modifier
 * 
 * @brief Modifie le texte
*/
void Text::setText(const std::string& newText)
{
    this->text = newText;

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surface == nullptr) {
        throw std::runtime_error("Failed to create surface: " + std::string(TTF_GetError()));
    }

    // Créer la texture à partir de la surface
    textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (textTexture == NULL) {
        std::cerr << "SDL_CreateTextureFromSurface Text: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_FreeSurface(surface);
}

std::string Text::getText()
{
    return this->text;
}

/**
 * @brief Charge la police.
*/
void Text::loadFont()
{
    font = TTF_OpenFont(fontPath.c_str(), 32);
    
    if (font == nullptr) {
        std::cerr << "TTF_OpenFont error in Text.cpp: " << TTF_GetError() << std::endl;
        exit(1);
    }
}