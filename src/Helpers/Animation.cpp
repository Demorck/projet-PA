#include <Helpers/Animation.hpp>

Animation::Animation(float x, float y, int width, int height, int nbFrame, int delay, const char* filepath, SDL_Renderer* renderer, SDL_Window* window)
    : x(x), y(y), width(width), height(height), nbFrame(nbFrame), delay(delay)
{
    this->createTextureFromSurface(filepath, renderer, window);
    tabImage[nbFrame] = (SDL_Texture*) malloc(nbFrame * sizeof(SDL_Texture*));
}

Animation::Animation(float x, float y, int width, int height, int nbFrame, int delay, const char* filepath)
    : x(x), y(y), width(width), height(height), nbFrame(nbFrame), delay(delay)
{
    tabImage[nbFrame] = (SDL_Texture*) malloc(nbFrame * sizeof(SDL_Texture*));
}

Animation::~Animation()
{

}

void Animation::animate(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, tabImage[0], NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Animation::createTextureFromSurface(const char* filepath, SDL_Renderer* renderer, SDL_Window* window)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(filepath);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", filepath, IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", filepath, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    tabImage[0] = SDL_CreateTextureFromSurface(renderer, optimizedSurface);
}