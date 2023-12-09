#include <UI/Button.hpp>
#include <iostream>

/**
 * @param renderer Le renderer pour le bouton
 * @param font : La police à utiliser
 * @param text : Le texte à inscrire dans le bouton
 * @param x : La position du bouton en abscisse
 * @param y : La position du bouton en ordonnée
 * @param width : La largeur du bouton
 * @param height : La hauteur du bouton
 * @param textColor : La couleur du texte
 * @param buttonColor : La couleur du bouton
 * @param buttonHoverColor : La couleur du bouton quand la souris est dessus
*/
Button::Button(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, int width, int height, SDL_Color textColor
                ,SDL_Color buttonColor, SDL_Color buttonHoverColor)
    : renderer(renderer), font(font), text(text), x(x), y(y), width(width), height(height), textColor(textColor), buttonColor(buttonColor), buttonHoverColor(buttonHoverColor)
{
    
    isPressed = false;
    hovering = false;

    // Créer la surface
    surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (surface == nullptr) {
        throw std::runtime_error("Failed to create surface: " + std::string(TTF_GetError()));
    }

    // Créer la texture à partir de la surface
    textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (textTexture == NULL) {
        std::cerr << "SDL_CreateTextureFromSurface Button: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

Button::Button()
{

}

/**
 * @brief Ferme la police et détruit la surface et les texture
*/
Button::~Button()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(surface);
}

/**
 * @brief Accorde les états du bouton en fonction de si on clique dessus ou si la souris est dessus.
*/
void Button::handleEvent(SDL_Event event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if(isPointInsideRect(event.button.x, event.button.y)) isPressed = true;
    }
    else if (event.type == SDL_MOUSEBUTTONUP) isPressed = false;
    else if (event.type == SDL_MOUSEMOTION) hovering = isPointInsideRect(event.button.x, event.button.y) ? true : false;
}

bool Button::pressed()
{
    return isPressed;
}

bool Button::isPointInsideRect(int mouseX, int mouseY)
{
    return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
}

/**
 * @brief Rendu du bouton
*/
void Button::render()
{
    SDL_Rect rect = { x, y, width, height };
    if (hovering) {
        SDL_SetRenderDrawColor(renderer, buttonHoverColor.r,  buttonHoverColor.g,  buttonHoverColor.b,  buttonHoverColor.a);
    } else {
        SDL_SetRenderDrawColor(renderer, buttonColor.r,  buttonColor.g,  buttonColor.b,  buttonColor.a);
    }
    
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);

    /**
     * Centre le texte 
    */
    SDL_Rect textRect = { x + width / 2, y + height / 2, 0, 0 };
    if (SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h) != 0) {
        std::cerr << "SDL_QueryTexture Button: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    textRect.x -= textRect.w / 2;
    textRect.y -= textRect.h / 2; 
    if (SDL_RenderCopy(renderer, textTexture, NULL, &textRect) != 0) {
        std::cerr << "SDL_RenderCopy Button: " << SDL_GetError() << std::endl;
        exit(1);
    }
}