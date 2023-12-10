#include <Enemy.hpp>
#include <iostream>

/**
 * @param hp : Le nombre de point de vie de l'ennemi
 * @param speed : La vitesse de l'ennemi
 * @param x, y : La position de l'ennemi
 * @param width, height : La largeur et hauteur de l'ennemi
 * @param renderer : Le renderer pour l'animation
*/
Enemy::Enemy(int hp, float speed, float x, float y, int width, int height, SDL_Renderer* renderer)
    : Entity(hp, speed, x, y, width, height)
{
    this->moveDown = false;
    this->moveUp = false;
    this->moveLeft = false;
    this->moveRight = false;
    
    animation = new Animation(x, y, WIDTH_ANIM_ENNEMY, HEIGHT_ANIM_ENNEMY, 1, 1.f, "assets/sprites/max.jpg", renderer);
}

Enemy::~Enemy()
{
    delete animation;
}

/**
 * @param renderer : Le renderer pour rendre l'ennemi sur l'écran
 * 
 * @brief Affiche l'ennemi et l'anime.
*/
void Enemy::render(SDL_Renderer* renderer)
{
    SDL_Rect rect = {(int)this->getX(), (int)this->getY(), this->getWidth(), this->getHeight()};
    this->animation->animate(renderer, rect);
}

/**
 * @param time : Le temps écoulé
 * 
 * @brief Met à jour l'ennemi et l'animation correspondante
*/
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

    this->animation->update(time);
}

/**
 * @param player : Le joueur en question
 * 
 * @return la distance entre le joueur et l'ennemi actuel (une norme euclidienne)
*/
float Enemy::distance(Player* player)
{
    return sqrt(pow(player->getX() - this->getX(), 2) + pow(player->getY() - this->getY(), 2));
}

/**
 * @param player : Le joueur
 * 
 * @brief Contrôle le comportement de l'ennemi. Il se dirige juste vers le joueur
*/
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
