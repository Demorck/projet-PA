#include <Enemy.hpp>
#include <iostream>


Enemy::Enemy(int hp, float speed, float x, float y, int width, int height)
    : Entity(hp, speed, x, y, width, height)
{
    this->moveDown = false;
    this->moveUp = false;
    this->moveLeft = false;
    this->moveRight = false;

}

Enemy::~Enemy()
{
    
}

void Enemy::render(SDL_Renderer* renderer)
{
    SDL_Rect rect = {(int)this->getX(), (int)this->getY(), this->getWidth(), this->getHeight()};   
    SDL_SetRenderDrawColor(renderer, 0, 0, 250, 0);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}

void Enemy::update(double time)
{
    if (this->moveRight)
        this->setX(this->getX() + this->getSpeed() * time);
    
    if (this->moveUp)
        this->setY(this->getY() - this->getSpeed() * time);
    
    if (this->moveLeft)
        this->setX(this->getX() - this->getSpeed() * time);
    
    if (this->moveDown)
        this->setY(this->getY() + this->getSpeed() * time);
}

float Enemy::distance(Player* player)
{
    return sqrt(pow(player->getX() - this->getX(), 2) + pow(player->getY() - this->getY(), 2));
}

void Enemy::behavior(Player* player)
{
    if (player->getX() < this->getX())
    {
        this->moveLeft = true;
        this->moveRight = false;
    }

    if (player->getX() > this->getX())
    {
        this->moveLeft = false;
        this->moveRight = true;
    }

    if (player->getY() < this->getY())
    {
        this->moveUp = true;
        this->moveDown = false;
    }

    if (player->getY() > this->getY())
    {
        this->moveUp = false;
        this->moveDown = true;
    }
    
}
