#include <Entity.hpp>
#include <iostream>

Entity::Entity(int hp, float speed, int x, int y)
    : hp(hp), speed(speed), x(x), y(y)
{
    this->moveDown = false;
    this->moveUp = false;
    this->moveLeft = false;
    this->moveRight = false;
}

Entity::~Entity()
{

}

void Entity::render(SDL_Renderer* renderer)
{
    SDL_Rect rect = {(int)x, (int)y, 60, 60};   
    SDL_SetRenderDrawColor(renderer, 250, 20, 20, 0);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}

void Entity::update(double time)
{
    if (this->moveRight)
        this->x += this->speed * time;
    
    if (this->moveUp)
        this->y -= this->speed * time;
    
    if (this->moveLeft)
        this->x -= this->speed * time;
    
    if (this->moveDown)
        this->y += this->speed * time;

}

void Entity::handleEvents()
{
    SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_q:
                            this->moveLeft = true;
                            this->moveRight = false;
                            break;
                        case SDLK_z:
                            this->moveUp = true;
                            this->moveDown = false;
                            break;
                        case SDLK_d:
                            this->moveRight = true;
                            this->moveLeft = false;
                            break;
                        case SDLK_s:
                            this->moveDown = true;
                            this->moveUp = false;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_q:
                            this->moveLeft = false;
                            break;
                        case SDLK_z:
                            this->moveUp = false;
                            break;
                        case SDLK_d:
                            this->moveRight = false;
                            break;
                        case SDLK_s:
                            this->moveDown = false;
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
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