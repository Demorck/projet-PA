#ifndef MAP_HPP
#define MAP_HPP
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Constant.hpp>

class Map
{
    public:
        Map(const char* textFileName, const char* tilemapFileName,  SDL_Window* window, SDL_Renderer* renderer);
        ~Map();

        void render(SDL_Renderer* renderer);
        
    private:
        const int nbSpritesPerLine = 2; // Nombre de sprite par ligne dans le fichier
        const int nbSpritesPerColumn = 2; // Nombre de sprite par colonne dans le fichier
        const int nbSprites = nbSpritesPerLine * nbSpritesPerColumn; // Nombre de sprite total


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
