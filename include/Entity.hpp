#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SDL2/SDL.h>

enum FACING_DIRECTION {UP, RIGHT, DON, LEFT}; 

class Entity
{
    public:
        Entity(int hp, float speed, int x, int y);
        ~Entity();
        void render(SDL_Renderer* renderer);
        void update();
        void handleEvents();

        int getHP();
        float getSpeed();

        void setHP(int hp);
        void setSpeed(float speed);

        int getX();
        int getY();

        void setX(int x);
        void setY(int y);
        void setFacing(FACING_DIRECTION facing);
    private:
        int x;
        int y;
        
        int hp;
        float speed;
        FACING_DIRECTION facing;
};

#endif