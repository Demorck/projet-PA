#include <Equipement.hpp>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <time.h>

/**
 * @param type : la catégorie de l'équipement 
 * @param color : La couleur de l'équipement
 * 
 * @brief Crée le carré aléatoirement et lui  donne une couleur
*/
Equipement::Equipement(int type, SDL_Color couleur)
{
    this->taille = 30;
    int maxw = SCREEN_WIDTH - this->taille ;
    this->cordx = rand() % maxw;

    
    int maxh = SCREEN_HEIGHT - this->taille;
    
    this->cordy = rand() % maxh;
    
    this->typ = type ;

    this->couleur = couleur;

}

Equipement::~Equipement()
{
}

/**
 * @param renderer : Le rendu pour afficher le carré
 * 
 * @brief Affiche le carré représentent l'equiment
*/

void Equipement::render(SDL_Renderer* renderer)
{
   
    SDL_Rect rect = {(int)this->cordx, (int)this->cordy, this->taille, this->taille};   
    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, couleur.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}
int Equipement::getX()
{
    return this->cordx;
}

int Equipement::getY()
{
    return this->cordy;
}

int Equipement::getType()
{
    return this->typ;
}


void Equipement::setX(int a)
{
    this->cordx = a;
}
void Equipement::setY(int a)
{
    this->cordy = a;
}

void Equipement::setType(int type)
{
    this->typ = type ;
}
void Equipement::setCouleur(SDL_Color couleur)
{
    this->couleur = couleur ;
}