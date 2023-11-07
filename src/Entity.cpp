#include <Entity.hpp>
#include <iostream>

Entity::Entity(int hp, float speed, float x, float y, int width, int height)
    : hp(hp), speed(speed), x(x), y(y), width(width), height(height)
{
    // this->animation = new Animation(x, y, width, height, 1, 1, "assets/sprites/player.png");
}

Entity::~Entity()
{

}

void Entity::render(SDL_Renderer* renderer)
{

}

void Entity::update(double time)
{

}

bool Entity::collision(float x, float y, int width, int height)
{
    if (this->x + this->width >= x &&
        this->x <= x + width &&
        this->y + this->height >= y &&
        this->y <= y + height)
        {
            return true;
        }
    return false;    
}

bool Entity::collision(Entity* entity)
{
    if (this->x + this->width >= entity->getX() &&
        this->x <= entity->getX() + entity->getWidth() &&
        this->y + this->height >= entity->getY() &&
        this->y <= entity->getY() + entity->getHeight())
        {
            return true;
        }
    return false;
}
bool Entity::collision(Equipement* equipement){
    if(this->x + this->width >= equipement->getX() &&
       this->x <= equipement->getX() + 30 &&
       this->y + this->height >= equipement->getY()&&
       this->y <= equipement->getY()+ 30){
            return true;
       }
    return false;
}

bool Entity::collision(Projectile* projectile)
{
    if (this->x + this->width >= projectile->getX() &&
        this->x <= projectile->getX() + 20 &&
        this->y + this->height >= projectile->getY() &&
        this->y <= projectile->getY() + 20)
        {
            return true;
        }
    return false;
}

bool Entity::collision(Equipement* equipement)
{
    if (this->x + this->width >= equipement->getX() &&
        this->x <= equipement->getX() + 30 &&
        this->y + this->height >= equipement->getY() &&
        this->y <= equipement->getY() + 30)
        {
            return true;
        }
    return false;
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

int Entity::getWidth()
{
    return this->width;
}

int Entity::getHeight()
{
    return this->height;
}

// Animation* Entity::getAnimation()
// {
//     return this->animation;
// }

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

void Entity::setWidth(int width)
{
    this->width = width;
}

void Entity::setHeight(int height)
{
    this->height = height;
}

void Entity::setFacing(MovingDirection facing)
{
    this->facing = facing; 
}