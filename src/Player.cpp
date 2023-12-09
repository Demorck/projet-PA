#include <Player.hpp>
#include <iostream>

/**
 * @param hp : Le nombre de point de vie de le joueur
 * @param speed : La vitesse de le joueur
 * @param x, y : La position de le joueur
 * @param width, height : La largeur et hauteur de le joueur
 * @param renderer : Le renderer pour l'animation
*/
Player::Player(int hp, float speed, float x, float y, int width, int height, SDL_Renderer* renderer)
    : Entity(hp, speed, x, y, width, height)
{
    this->moveDown = false;
    this->moveUp = false;
    this->moveLeft = false;
    this->moveRight = false;
    
    animation = new Animation(x, y, width, height, 4, 1.f, "assets/sprites/player2.png", renderer);
    
}

Player::~Player()
{
    
}

/**
 * @param renderer : Le renderer pour rendre le joueur sur l'écran
 * 
 * @brief Affiche le joueur et l'anime.
*/
void Player::render(SDL_Renderer* renderer)
{
    SDL_Rect rect = {(int)this->getX(), (int)this->getY(), this->getWidth(), this->getHeight()};
    this->animation->animate(renderer, rect);
}

/**
 * @param time : Le temps écoulé
 * 
 * @brief Met à jour le joueur et l'animation correspondante
*/
void Player::update(double time)
{
    /* Permet de mouvoir le joueur ici */
    if (this->moveRight)
        this->setX(this->getX() + this->getSpeed() * time);

    if (this->moveUp)
        this->setY(this->getY() - this->getSpeed() * time);
    
    if (this->moveLeft)
        this->setX(this->getX() - this->getSpeed() * time);
    
    if (this->moveDown)
        this->setY(this->getY() + this->getSpeed() * time);
    /********************************/

    /* Permet de ne pas faire sortir le joueur en dehors de l'écran */
    if (this->getX() + this->getWidth() > SCREEN_WIDTH)
        this->setX(SCREEN_WIDTH - this->getWidth());

    if (this->getY() + this->getHeight() > SCREEN_HEIGHT)
        this->setY(SCREEN_HEIGHT - this->getHeight());

    if (this->getX() < 0)
        this->setX(0);

    if (this->getY() < 0)
        this->setY(0);
    /***************************************************************/
    
    this->animation->update(time);
}

/**
 * @param move : Permet de voir de quelle direction on bouge
 * @param isMoving : Permet de mettre la direction à false ou true
 * 
 * @brief Modifie les états des directions où on bouge
*/
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

/**
 * @param move : Permet de savoir sur quelle direction on bouge
 * 
 * @return l'état de la direction 
*/
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