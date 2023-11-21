#include <Equipement.hpp>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <time.h>


Equipement::Equipement(/* args */)
{
    srand(time(NULL));

    int minw = 1; 
    int maxw = SCREEN_WIDTH;
    this->cordx = rand() % maxw;

    
    int minh = 1; 
    int maxh = SCREEN_HEIGHT;
    
    this->cordy = rand() % maxh;
    


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

void Equipement::setX(int a)
{
    this->cordx = a;
}
void Equipement::setY(int a)
{
    this->cordy = a;
}