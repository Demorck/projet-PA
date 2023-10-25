#ifndef EQUIPEMENT_HPP
#define EQUIPEMENT_HPP
#include <SDL2/SDL.h>

class Equipement
{
    private:
        int cordx;
        int cordy;
    public:
        Equipement(/* args */);
        ~Equipement();
        void   render(SDL_Renderer* renderer);
};








#endif