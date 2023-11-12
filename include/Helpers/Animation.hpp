#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Animation
{
    public:
        Animation(float x, float y, int width, int height, int nbFrame, float delay, const char* filepath, SDL_Renderer* renderer, SDL_Window* window);
        ~Animation();

        void animate(SDL_Renderer* renderer, SDL_Rect where);
        void update(float deltaTime);
        void createTextureFromSurface(const char* filepath, SDL_Renderer* renderer, SDL_Window* window);
        
    private:
        float x;
        float y;
        int width;
        int height;
        
        int nbFrame;
        float delay;
        float elapsedTime;
        SDL_Rect* tabImage; 
        int currentFrame;
        SDL_Texture* spriteSheet;

        void createRectangles();

};

#endif