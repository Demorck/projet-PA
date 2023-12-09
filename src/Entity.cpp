#include <Entity.hpp>
#include <iostream>
#include <fstream>

/**
 * @param hp : Le nombre de point de vie de l'ennemi
 * @param speed : La vitesse de l'ennemi
 * @param x, y : La position de l'ennemi
 * @param width, height : La largeur et hauteur de l'ennemi
*/
Entity::Entity(int hp, float speed, float x, float y, int width, int height)
    : hp(hp), speed(speed), x(x), y(y), width(width), height(height)
{
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

/**
 * @param x, y : la position de l'autre chose à voir si on collisionne avec
 * @param width, height : Pareil mais pour la hauteur
 * 
 * @return true si l'un est dans l'autre ; false sinon
*/
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

/**
 * @param entity : Une autre entité 
 * 
 * @return true si l'un est dans l'autre ; false sinon
*/
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

/**
 * @param equipement : Un equipement
 * 
 * @return true si l'un est dans l'autre ; false sinon
*/
bool Entity::collision(Equipement* equipement){
    if(this->x + this->width >= equipement->getX() &&
       this->x <= equipement->getX() + 30 &&
       this->y + this->height >= equipement->getY()&&
       this->y <= equipement->getY() + 30){
            return true;
       }
    return false;
}

/**
 * @param projectile : Un projectile
 * 
 * @return true si l'un est dans l'autre ; false sinon
*/
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

/**
 * @param bar : Une bar (pour la bar d'HP)
 * 
 * @return true si l'un est dans l'autre ; false sinon
*/
bool Entity::collision(Bar* bar){
    SDL_Rect r = bar->getRect();
    if(this->x + this->width >= r.x &&
       this->x <= r.x + r.w &&
       this->y + this->height >= r.y &&
       this->y <= r.y + r.h){
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

Animation* Entity::getAnimation()
{
    return this->animation;
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

void Entity::setWidth(int width)
{
    this->width = width;
}

void Entity::setHeight(int height)
{
    this->height = height;
}

/**
 * @param file : Le fichier à sauvegarder l'état
 * 
 * @brief Sauvegarde l'état de l'entité (en particulier, les PV, la vitesse et la position et taille)
*/
void Entity::save(std::ofstream& file)
{
    if (file.is_open())
    {
        file.write(reinterpret_cast<const char*>(&hp), sizeof(hp));
        file.write(reinterpret_cast<const char*>(&speed), sizeof(speed));
        file.write(reinterpret_cast<const char*>(&x), sizeof(x));
        file.write(reinterpret_cast<const char*>(&y), sizeof(y));
        file.write(reinterpret_cast<const char*>(&width), sizeof(width));
        file.write(reinterpret_cast<const char*>(&height), sizeof(height));
    }
    else
    {
        std::cerr << "Unable to open file for writing. " << std::endl;
    }
}

/**
 * @param file : Le fichier à charger l'état
 * 
 * @brief Charge l'état de l'entité (en particulier, les PV, la vitesse et la position et taille)
*/
void Entity::load(std::ifstream& file)
{
    if (file.is_open())
    {
        file.read(reinterpret_cast<char*>(&hp), sizeof(hp));
        file.read(reinterpret_cast<char*>(&speed), sizeof(speed));
        file.read(reinterpret_cast<char*>(&x), sizeof(x));
        file.read(reinterpret_cast<char*>(&y), sizeof(y));
        file.read(reinterpret_cast<char*>(&width), sizeof(width));
        file.read(reinterpret_cast<char*>(&height), sizeof(height));
    }
    else
    {
        std::cerr << "Unable to open file for reading." << std::endl;
    }
}