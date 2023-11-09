#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Animation
{
    public:
        Animation(float x, float y, int width, int height, int nbFrame, int delay, const char* filepath, SDL_Renderer* renderer, SDL_Window* window);
        Animation(float x, float y, int width, int height, int nbFrame, int delay, const char* filepath);
        ~Animation();

        void animate(SDL_Renderer* renderer);
        void createTextureFromSurface(const char* filepath, SDL_Renderer* renderer, SDL_Window* window);
        
    private:
        float x;
        float y;
        int width;
        int height;
        
        int nbFrame;
        int delay;
        SDL_Texture* tabImage[5]; 

        SDL_Window* window;

};

#endif