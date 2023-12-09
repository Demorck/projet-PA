#include <Projectile.hpp>
#include <math.h>

/**
 * @param x, y : La position de le joueur
 * @param angle : L'angle du projectile à lancer
 * @param speed : La vitesse du projectile
*/
Projectile::Projectile(float x, float y, float angle, float speed)
            : x(x), y(y), angle(angle), speed(speed)
{
}

Projectile::~Projectile()
{
}

/**
 * @param deltaTime : le temps écoulé
 * 
 * @brief Met à jour les coordonnées du projectile
*/
void Projectile::update(float deltaTime)
{
    x += cos(angle) * speed * deltaTime;
    y += sin(angle) * speed * deltaTime;
}

/**
 * @param renderer : Le renderer pour rendre le projectile
*/
void Projectile::render(SDL_Renderer* renderer)
{
    SDL_Rect r = {x, y, 5, 5};
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderDrawRect(renderer, &r);
}

float Projectile::getX()
{
    return this->x;
}

float Projectile::getY()
{
    return this->y;
}

float Projectile::getSpeed()
{
    return this->speed;
}

void Projectile::setX(float x)
{
    this->x = x;
}

void Projectile::setY(float y)
{
    this->y = y;
}

void Projectile::setSpeed(float speed)
{
    this->speed = speed;
}
