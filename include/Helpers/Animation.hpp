#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SDL2/SDL.h>
#include <iostream>

class Animation
{
    public:
        Animation(float x, float y, int width, int height, int nbFrame, int delay, const char* filepath, SDL_Renderer* renderer);
        ~Animation();

        void animate(SDL_Renderer* renderer);
        
    private:
        float x;
        float y;
        int width;
        int height;
        
        int nbFrame;
        int delay;
        SDL_Texture* tabImage[]; 

        void createTextureFromSurface(const char* filepath, SDL_Renderer* renderer);
};

#endif