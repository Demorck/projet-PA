#include <Player.hpp>
#include <iostream>

Player::Player(int hp, float speed, float x, float y, int width, int height)
    : Entity(hp, speed, x, y, width, height)
{
    this->moveDown = false;
    this->moveUp = false;
    this->moveLeft = false;
    this->moveRight = false;
    Render& r = Render::getInstance();
    animation = new Animation(x, y, width, height, 4, 1.f, "assets/sprites/player2.png", r.getRenderer());
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_Rect rect = {(int)this->getX(), (int)this->getY(), this->getWidth(), this->getHeight()};
    this->animation->animate(renderer, rect);   
    // SDL_SetRenderDrawColor(renderer, 250, 20, 20, 0);
    // SDL_RenderFillRect(renderer, &rect);
    // SDL_RenderDrawRect(renderer, &rect);
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

    if (this->getX() + this->getWidth() > SCREEN_WIDTH)
        this->setX(SCREEN_WIDTH - this->getWidth());

    if (this->getY() + this->getHeight() > SCREEN_HEIGHT)
        this->setY(SCREEN_HEIGHT - this->getHeight());

    if (this->getX() < 0)
        this->setX(0);

    if (this->getY() < 0)
        this->setY(0);
    
    
    this->animation->update(time);
}

void Player::move(MovingDirection move, bool isMoving)
{
    switch (move)
    {
        case LEFT:
            this->moveLeft = isMoving;
            break;
        case RIGHT:
            this->moveRight = isMoving;
            break;
        case UP:
            this->moveUp = isMoving;
            break;
        case DOWN:
            this->moveDown = isMoving;
            break;
        default:
            break;
    }

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

bool Player::isMoving(MovingDirection move)
{
    switch (move)
    {
        case LEFT:
            return true;
            break;
        case RIGHT:
            return true;
            break;
        case UP:
            return true;
            break;
        case DOWN:
            return true;
            break;
        default:
            return false;
            break;
    }
}