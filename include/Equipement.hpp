#ifndef EQUIPEMENT_HPP
#define EQUIPEMENT_HPP
#include <SDL2/SDL.h>
#include <Constant.hpp>

class Equipement
{
    private:
        int cordx;
        int cordy;
        //int typ;
    public:
        Equipement(/* args */);
        ~Equipement();
        void   render(SDL_Renderer* renderer);
        int getX();
        int getY();
        void setX(int a);
        void setY(int a);
};








#endif