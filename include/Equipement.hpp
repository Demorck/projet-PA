#ifndef EQUIPEMENT_HPP
#define EQUIPEMENT_HPP
#include <SDL2/SDL.h>
#include <Constant.hpp>

class Equipement
{
    private:
        int cordx;
        int cordy;
    public:
        Equipement(/* args */);
        ~Equipement();
        void   render(SDL_Renderer* renderer);
        int getX();
        int getY();
};








#endif