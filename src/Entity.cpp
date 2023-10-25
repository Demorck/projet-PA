#include <Entity.hpp>
#include <iostream>

Entity::Entity(int hp, float speed, int x, int y)
    : hp(hp), speed(speed), x(x), y(y)
{
}

// Entity::Entity()
// {

// }

Entity::~Entity()
{

}

void Entity::render(SDL_Renderer* renderer)
{

}

void Entity::update(double time)
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

void Entity::setX(float x)
{
    this->x = x;
}

void Entity::setY(float y)
{
    this->y = y;
}

void Entity::setFacing(FACING_DIRECTION facing)
{
    this->facing = facing; 
}

int Entity::getHP()
{
    return this->hp;
}

float Entity::getSpeed()
{
    return this->speed;
}

float Entity::getX()
{
    return this->x;
}

float Entity::getY()
{
    return this->y;
}