#ifndef EQUIPEMENT_HPP
#define EQUIPEMENT_HPP
#include <SDL2/SDL.h>
#include <Constant.hpp>

class Equipement
{
    private:
        int cordx;
        int cordy;
        int typ; //en fonction de la valeur le bonus apporter et différente 
        SDL_Color couleur;

    public:
        Equipement(int typ,SDL_Color couleur);
        ~Equipement();
        void   render(SDL_Renderer* renderer);
        int getX();
        int getY();
        int getType();
        
        void setX(int x);
        void setY(int y);
        void setType(int t);
        void setCouleur(SDL_Color couleur);
};








#endif