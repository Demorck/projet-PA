#include <Entity.hpp>
#include <iostream>

Entity::Entity(int hp, float speed, int x, int y)
    : hp(hp), speed(speed), x(x), y(y)
{

}

Entity::~Entity()
{

}

void Entity::render(SDL_Renderer* renderer)
{
    SDL_Rect rect = {x, y, 40, 40};   
    SDL_SetRenderDrawColor(renderer, 250, 20, 20, 0);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}

void Entity::handleEvents()
{

}

void Entity::setHP(int hp)
{
    this->hp = hp;
}

void Entity::setSpeed(float speed)
{
    this->speed = speed;
}

void Entity::setX(int x)
{
    this->x = x;
}

void Entity::setY(int y)
{
    this->y = y;
}

int Entity::getHP()
{
    return this->hp;
}

float Entity::getSpeed()
{
    return this->speed;
}

int Entity::getX()
{
    return this->x;
}

int Entity::getY()
{
    return this->y;
}