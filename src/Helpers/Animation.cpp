#include <Helpers/Animation.hpp>

/**
 * @param x : position x de l'animation
 * @param y : position y de l'animation
 * @param width : largeur de l'animation (et des sprites)
 * @param height : hauteur de l'animation (et des sprites)
 * @param nbFrame : nombre de frame qu'a l'animation (différent de 0)
 * @param delay : delay en ms de chaque frame
 * @param filepath : Chemin vers le fichier du spritesheet
 * @param renderer : le renderer
 * @param window : la fenêtre
 * 
 * @brief Créer l'animation et les rectangles pour le spritesheet
*/
Animation::Animation(float x, float y, int width, int height, int nbFrame, float delay, const char* filepath, SDL_Renderer* renderer)
    : x(x), y(y), width(width), height(height), nbFrame(nbFrame), delay(delay)
{
    this->createTextureFromSurface(filepath, renderer);
    currentFrame = 0;
    tabImage = (SDL_Rect*)malloc(nbFrame * sizeof(SDL_Rect));
    this->createRectangles();

}

Animation::~Animation()
{
    free(tabImage);
    SDL_DestroyTexture(spriteSheet);
}

/**
 * @param renderer : Le renderer
 * @param where : Le rectangle de destination sur l'écran
 * 
 * @brief Anime l'animation courante. 
*/
void Animation::animate(SDL_Renderer* renderer, SDL_Rect where)
{
    SDL_RenderCopy(renderer, spriteSheet, &tabImage[currentFrame], &where);
}

/**
 * @param deltaTime le temps actuel.
 * 
 * @brief Update l'animation et change la frame actuelle si le temps entre chaque est supérieur au delay
*/
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

/**
 * @param filepath : Le chemin vers le spritesheet
 * @param renderer : Le renderer
 * 
 * @brief Crée la texture et le mets dans la variable locale spriteSheet depuis un chemin
*/
void Animation::createTextureFromSurface(const char* filepath, SDL_Renderer* renderer)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(filepath);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", filepath, IMG_GetError() );
    }

    spriteSheet = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface( loadedSurface );
}

/**
 * @brief Crée les rectangles depuis le spriteSheet
*/
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