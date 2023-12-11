#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <Entity.hpp>
#include <Helpers/Animation.hpp>
#include <Constant.hpp>


class Player : public Entity
{   
    public:
        Player(int hp, float speed, float x, float y, int width, int height, SDL_Renderer* renderer);
        ~Player();
        void render(SDL_Renderer* renderer);
        void update(double time);

        bool isMoving(MovingDirection move);
        void move(MovingDirection move, bool isMoving);

        double getShootDelay();
        void setShootDelay(double delay);

    
    private:
        bool moveLeft;
        bool moveRight; 
        bool moveDown;
        bool moveUp;

        Animation* animation; 

        double shootDelay = .5f;
};

#endif