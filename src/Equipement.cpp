#include <Equipement.hpp>
#include <iostream>
#include <stdlib.h>
#include <random>


Equipement::Equipement(/* args */)
{
   
    int minw = 1; 
    int maxw = 1070;
    this->cordx = std::rand() % maxw;

    int minh = 1; 
    int maxh = 710;
    
    this->cordy = std::rand() % maxh;
}

Equipement::~Equipement()
{
}



void Equipement::render(SDL_Renderer* renderer)
{
   
    SDL_Rect rect = {(int)this->cordx, (int)this->cordy, 30, 30};   
    SDL_SetRenderDrawColor(renderer, 0, 250, 0, 250);
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
