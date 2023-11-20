#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <Entity.hpp>
#include <Helpers/Animation.hpp>
#include <Player.hpp>
#include <math.h>

class Enemy : public Entity
{
    public:
        Enemy(int hp, float speed, float x, float y, int width, int height, SDL_Renderer* renderer);
        ~Enemy();
        void render(SDL_Renderer* renderer);
        void update(double time);
        void behavior(Player* player);
        float distance(Player* player);
    private:
        bool moveLeft;
        bool moveRight; 
        bool moveDown;
        bool moveUp;
        
        Animation* animation; 
};

#endif