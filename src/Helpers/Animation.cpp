#include <Helpers/Animation.hpp>

Animation::Animation(float x, float y, int width, int height, int nbFrame, float delay, const char* filepath, SDL_Renderer* renderer, SDL_Window* window)
    : x(x), y(y), width(width), height(height), nbFrame(nbFrame), delay(delay)
{
    this->createTextureFromSurface(filepath, renderer, window);
    currentFrame = 0;
    tabImage = (SDL_Rect*)malloc(nbFrame * sizeof(SDL_Rect));
    this->createRectangles();

}

Animation::~Animation()
{
    free(tabImage);
    SDL_DestroyTexture(spriteSheet);
}

void Animation::animate(SDL_Renderer* renderer, SDL_Rect where)
{
    if (SDL_SetTextureBlendMode(spriteSheet, SDL_BLENDMODE_NONE) == -1) printf("feur");
    SDL_RenderCopy(renderer, spriteSheet, &tabImage[currentFrame], &where);
    // SDL_RenderPresent(renderer);
}

void Animation::update(float deltaTime)
{
    elapsedTime += deltaTime;
    
    if (elapsedTime >= delay)
    {
        currentFrame++;
        if (currentFrame == nbFrame)
        {
            currentFrame = 0;
        }

        elapsedTime = 0.0f;
    }
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
        
        if( optimizedSurface == NULL)
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", filepath, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    spriteSheet = SDL_CreateTextureFromSurface(renderer, optimizedSurface);
}

void Animation::createRectangles()
{
    SDL_Point size;
    SDL_QueryTexture(spriteSheet, NULL, NULL, &size.x, &size.y);

    for(int i = 0; i < nbFrame; i++){
        tabImage[i] = {0, 0, 0, 0};
    }

    for (int i = 0; i < nbFrame; i++)
    {
        SDL_Rect currentRect;
        currentRect.x = i*width;
        currentRect.y = 0;
        currentRect.w = width;
        currentRect.h = height;

        tabImage[i] = currentRect;
    }
}