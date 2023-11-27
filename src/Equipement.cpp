#include <Equipement.hpp>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <time.h>


Equipement::Equipement(int type, SDL_Color couleur)
{

    int minw = 1; 
    int maxw = SCREEN_WIDTH;
    this->cordx = rand() % maxw;

    
    int minh = 1; 
    int maxh = SCREEN_HEIGHT;
    
    this->cordy = rand() % maxh;
    
    this->typ = type ;

    this->couleur = couleur;
}

Equipement::~Equipement()
{
}



void Equipement::render(SDL_Renderer* renderer)
{
   
    SDL_Rect rect = {(int)this->cordx, (int)this->cordy, 30, 30};   
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