#ifndef MAP_HPP
#define MAP_HPP
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Map
{
    public:
        Map(const char* textFileName, const char* tilemapFileName,  SDL_Window* window, SDL_Renderer* renderer);
        ~Map();

        void render(SDL_Renderer* renderer);
        
    private:
        const int nbSpritesPerLine = 2;
        const int nbSpritesPerColumn = 2;
        const int nbSprites = nbSpritesPerLine * nbSpritesPerColumn;


        void fileSize(FILE* file);
        void readFile(const char* fileName);
        void allocate2Dtab();

        const char* textFileName;

        int** tab;
        SDL_Rect* tabRect;
        SDL_Rect* rectOnScreen;

        int nbLin;
        int nbCol;
        SDL_Texture* tilemap;
};

#endif