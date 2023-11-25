#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SDL2/SDL.h>
#include <Projectile.hpp>
#include <Equipement.hpp>
#include <UI/Bar.hpp>
#include <Helpers/Animation.hpp>

enum MovingDirection {UP, RIGHT, DOWN, LEFT, IDLE}; 

class Entity
{
    public:
        Entity(int hp, float speed, float x, float y, int width, int height);
        // Entity();
        ~Entity();
        virtual void render(SDL_Renderer* renderer);
        void update(double time);
        bool collision(float x, float y, int width, int height);
        bool collision(Entity* entity);
        bool collision(Projectile* projectile);
        bool collision(Equipement* equipement);
        bool collision(Bar* bar);

        int getHP();
        float getSpeed();
        float getX();
        float getY();
        int getWidth();
        int getHeight();
        virtual Animation* getAnimation();

        void setHP(int hp);
        void setSpeed(float speed);
        void setX(float x);
        void setY(float y);
        void setWidth(int width);
        void setHeight(int height);       

        void setFacing(MovingDirection facing);

        void save(std::ofstream& file);
        void load(std::ifstream& file);
    private:
        float x;
        float y;
        int width;
        int height;
        
        int hp;
        float speed;
        MovingDirection facing;

        Animation* animation;
};

#endif