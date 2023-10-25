#include <Player.hpp>

Player::Player(int hp, float speed, int x, int y)
    : Entity(hp, speed, x, y)
{
    this->moveDown = false;
    this->moveUp = false;
    this->moveLeft = false;
    this->moveRight = false;
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_Rect rect = {(int)this->getX(), (int)this->getY(), 60, 60};   
    SDL_SetRenderDrawColor(renderer, 250, 20, 20, 0);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}

void Player::update(double time)
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


void Player::handleEvents()
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