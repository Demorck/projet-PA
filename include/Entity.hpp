#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SDL2/SDL.h>

enum FACING_DIRECTION {UP, RIGHT, DOWN, LEFT, IDLE}; 

class Entity
{
    public:
        Entity(int hp, float speed, int x, int y);
        ~Entity();
        void render(SDL_Renderer* renderer);
        void update(double time);
        void handleEvents();

        int getHP();
        float getSpeed();

        void setHP(int hp);
        void setSpeed(float speed);

        float getX();
        float getY();

        void setX(float x);
        void setY(float y);
        void setFacing(FACING_DIRECTION facing);
    private:
        float x;
        float y;
        
        int hp;
        float speed;
        FACING_DIRECTION facing;

        bool moveLeft;
        bool moveRight; 
        bool moveDown;
        bool moveUp;
};

#endif