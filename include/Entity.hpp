#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SDL2/SDL.h>

class Entity
{
    public:
        Entity(int hp, float speed, int x, int y);
        ~Entity();
        void render(SDL_Renderer* renderer);
        void handleEvents();

        int getHP();
        int getSpeed();

        void setHP(int hp);
        void setSpeed(float speed);

        int getX();
        int getY();

        void setX(int x);
        void setY(int y);

    private:
        int x;
        int y;
        
        int hp;
        float speed;

};

#endif