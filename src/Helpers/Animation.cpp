#include <Helpers/Animation.hpp>

Animation::Animation(float x, float y, int width, int height, int nbFrame, int delay, const char* filepath, SDL_Renderer* renderer)
    : x(x), y(y), width(width), height(height), nbFrame(nbFrame), delay(delay)
{
    this->createTextureFromSurface(filepath, renderer);
    tabImage[nbFrame] = (SDL_Texture*) malloc(nbFrame * sizeof(SDL_Texture*));
}

Animation::~Animation()
{

}

void Animation::createTextureFromSurface(const char* filepath, SDL_Renderer* renderer)
{
    SDL_Surface* surface = SDL_LoadBMP(filepath);
    for (int i = 0; i < this->nbFrame; i++)
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    
}