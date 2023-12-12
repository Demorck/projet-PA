#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include <SDL2/SDL.h>

class Projectile
{
    public:
        Projectile(float x, float y, float angle, float speed);
        ~Projectile();

        void update(float deltaTime);
        void render(SDL_Renderer* renderer);

        float getX();
        float getY();
        float getSpeed();

        void setX(float x);
        void setY(float y);
        void setSpeed(float speed);

    private:
        float x;
        float y;
        float angle;
        float speed;
};

#endif