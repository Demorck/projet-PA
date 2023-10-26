#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <Entity.hpp>
#include <Player.hpp>

class Enemy : public Entity
{
    public:
        Enemy(int hp, float speed, float x, float y, int width, int height);
        ~Enemy();
        void render(SDL_Renderer* renderer);
        void update(double time);
        void behavior(Player* player);
    private:
        bool moveLeft;
        bool moveRight; 
        bool moveDown;
        bool moveUp;

};

#endif