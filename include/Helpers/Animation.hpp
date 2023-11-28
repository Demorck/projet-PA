#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <UI/Render.hpp>
#include <iostream>

class Animation
{
    public:
        Animation(float x, float y, int width, int height, int nbFrame, float delay, const char* filepath, SDL_Renderer* renderer);
        ~Animation();

        void animate(SDL_Renderer* renderer, SDL_Rect where);
        void update(float deltaTime);
        void createTextureFromSurface(const char* filepath, SDL_Renderer* renderer);
        
    private:
        float x;
        float y;
        int width;
        int height;
        
        int nbFrame;
        float delay;
        float elapsedTime = 0.f;
        SDL_Rect* tabImage; 
        int currentFrame;
        SDL_Texture* spriteSheet;

        void createRectangles();

};

#endif