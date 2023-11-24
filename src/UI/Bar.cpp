#include <UI/Bar.hpp>

/**
 * @param x : La position x de la barre horizontale
 * @param y : La position y de la barre horizontale
 * @param w : La largeur w de la barre horizontale
 * @param h : Une série française avec Jamel (et aussi la hauteur de la barre horizontale)
 * @param color : La couleur de la barre
 * 
 * @brief Crée le rectangle avec SDL_Rect et la couleur
*/
Bar::Bar(int x, int y, int w, int h, SDL_Color color) :
    barRect({x, y, w, h}), color(color)
{
}

/**
 * @param rect : Le rectangle
 * @param color : La couleur de la barre
 * 
 * @brief Crée le rectangle avec SDL_Rect et la couleur
*/
Bar::Bar(SDL_Rect rect, SDL_Color color) :
    barRect(rect), color(color)
{

}

Bar::~Bar()
{
}

/**
 * @param renderer : Le rendu pour afficher le rectangle
 * 
 * @brief Affiche le rectangle
*/
void Bar::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &barRect);
    SDL_RenderDrawRect(renderer, &barRect);
}

void Bar::setWidth(int w)
{
    this->barRect.w = w;
}

SDL_Rect Bar::getRect()
{
    return this->barRect;
}

/**
 * @brief Bouge la barre si elle doit être à gauche ou à droite.
*/
void Bar::moveBar()
{
    if (onLeft)
    {
        barRect.x = SCREEN_WIDTH - barRect.w - 10;
        onLeft = !onLeft;
    }
    else
    {
        barRect.x = 10;
        onLeft = !onLeft;
    }
    
}