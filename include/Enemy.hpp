#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <Entity.hpp>
#include <Player.hpp>

class Enemy : public Entity
{
    public:
        Enemy(int hp, float speed, int x, int y);
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