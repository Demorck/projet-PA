#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Map.hpp>

Map::Map(const char* textFileName, const char* tilemapFileName, SDL_Window* window, SDL_Renderer* renderer)
    : textFileName(textFileName)
{
    nbCol = 0;
    nbLin = 0;
    
    readFile(textFileName);

    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(tilemapFileName);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", tilemapFileName, IMG_GetError() );
    }
    else
    {
        
        optimizedSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface(window)->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", tilemapFileName, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    tilemap = SDL_CreateTextureFromSurface(renderer, optimizedSurface);

    SDL_Point size;
    SDL_QueryTexture(tilemap, NULL, NULL, &size.x, &size.y);

    tabRect =(SDL_Rect*)malloc(nbLin * sizeof(SDL_Rect));

    for(int i = 0; i < nbSprites; i++){
        tabRect[i] = {0, 0, 0, 0};
    }

    for (int i = 0; i < nbSprites; i++)
    {
        SDL_Rect currentRect;
        currentRect.x = (i % nbSpritesPerLine) * (size.x / nbSpritesPerLine);
        currentRect.y = (i / nbSpritesPerLine) * (size.y / nbSpritesPerColumn);
        currentRect.w = (size.x / nbSpritesPerColumn);
        currentRect.h = (size.y / nbSpritesPerColumn);

        tabRect[i] = currentRect;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    rectOnScreen = (SDL_Rect*)malloc(nbLin * nbCol * sizeof(SDL_Rect));

    int nbOfRectangles = nbLin * nbCol;

    for (int i = 0; i < nbOfRectangles; i++)
    {
        rectOnScreen[i] = {0, 0, 0, 0};
    }  

    for (int i = 0; i < nbOfRectangles; i++)
    {
        SDL_Rect currentRect;
        currentRect.x = (i % nbLin) * (size.x / nbSpritesPerLine);
        currentRect.y = (i / nbLin) * (size.y / nbSpritesPerColumn);
        currentRect.w = size.x / nbSpritesPerLine;
        currentRect.h = size.y / nbSpritesPerColumn;

        rectOnScreen[i] = currentRect;
    }

    
}

Map::~Map()
{
    for (int i = 0; i < nbLin; i++)
        free(tab[i]);

    free(tab);
    free(rectOnScreen);
}

void Map::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < nbLin; i++)
    {
        for (int j = 0; j < nbCol; j++)
        {
            // Vérifiez que i et j sont dans les limites
            if (i < nbLin && j < nbCol)
            {
                // Si on met des numéros non autorisés
                if (tab[i][j] >= 0 && tab[i][j] < nbSprites)
                {
                    SDL_Rect currentRect = tabRect[tab[i][j]];
                    SDL_RenderCopy(renderer, tilemap, &currentRect, &rectOnScreen[i * nbCol + j]);
                }
            }
        }
    }
}

void Map::fileSize(FILE* file)
{
    int current_col = 0;
    int max_col = 0;

    int c;
	while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            nbLin++;
            max_col = (current_col > max_col) ? current_col : max_col;
            current_col = 0;
        } else {
            current_col++;
        }
    }
	if (current_col > 0) {
        nbLin++;
        max_col = (current_col > max_col) ? current_col : max_col;
    }

    nbCol = max_col;
}

void Map::readFile(const char* textFileName)
{
    FILE* file = fopen(textFileName, "r");
    if (file == NULL) {
        printf("Impossible d’ouvrir le fichier.\n");
        return;
    }

    fileSize(file);

    allocate2Dtab();

    if (tab == NULL) {
        fclose(file);
        return;
    }

    fseek(file, 0, SEEK_SET);
    int lig = 0;
    int col = 0;
    int c;

    
    if (feof(file)) {
        printf("Le fichier est déjà à la fin.\n");
    }
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lig++;
            col = 0;
        } else {
            tab[lig][col] = (char)c - '0';
            col++;
        }
    }

    fclose( file );
}

void Map::allocate2Dtab(){
    tab = (int**)malloc(nbLin * sizeof(int*));

    if(tab == NULL)
        return;

    for (int i = 0; i < nbLin; i++) {
        tab[i] = (int*)calloc(nbCol, sizeof(int));

        if (tab[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(tab[j]);
            }
            free(tab);
            return;
        }
    }
}
