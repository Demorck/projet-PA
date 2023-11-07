#include <Projectile.hpp>
#include <math.h>

Projectile::Projectile(float x, float y, float angle, float speed)
            : x(x), y(y), angle(angle), speed(speed)
{

}

Projectile::~Projectile()
{

}

void Projectile::update(float deltaTime)
{
    x += cos(angle) * speed * deltaTime;
    y += sin(angle) * speed * deltaTime;
}

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
