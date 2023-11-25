#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Map.hpp>

/**
 * @param textFileName La source du fichier texte pour créer la carte
 * @param tilemapFileName La source du fichier png pour créer les sprites de la map
 * @param window La fenêtre SDL pour rendre la surface
 * @param renderer La fenêtre SDL pour rendre dans render
 * 
 * Le constructeur lit le fichier texte et créer 2 tableaux : un tableau de SDL_Rect appelé tabRect qui sauvegarde l'emplacement des rectangles des sprites
 * L'autre est un SDL_Rect appelé rectOnScreen qui calcule où il doit afficher les différents sprite sur l'écran.
*/
Map::Map(const char* textFileName, const char* tilemapFileName, SDL_Renderer* renderer)
    : textFileName(textFileName)
{
    nbCol = 0;
    nbLin = 0;
    
    /**
     * Lit le fichier et store le nombre de lignes et de colonne dans nbLin et nbCol
    */
    readFile(textFileName);
    
    
    

    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(tilemapFileName);
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", tilemapFileName, IMG_GetError() );
    }

    tilemap = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    // Récupère la taille du fichier de sprite
    SDL_Point size;
    SDL_QueryTexture(tilemap, NULL, NULL, &size.x, &size.y);

    // ********************************************************* //
    tabRect =(SDL_Rect*)malloc(nbLin * sizeof(SDL_Rect));

    // Initialise tous les rectangles à zéro
    for(int i = 0; i < nbSprites; i++){
        tabRect[i] = {0, 0, 0, 0};
    }

    /**
     * *  Dans le header, il y a 2 paramètres : le nombre de sprite par ligne et par colonne.
     * * La largeur de chaque sprite est de la taille de la spritesheeet / nombre de sprite par ligne. Pareil pour la hauteur
     * * Niveau positionnement, c'est un for-loop de i jusqu'au nombre de sprite. Niveau abscisse, on change tout le temps et on revient à zéro dès qu'on a notre nombre de sprite par ligne
     * * Niveau ordonnée, il faut changer dès que la ligne change. C'est la partie entière d'une division.
    */
    for (int i = 0; i < nbSprites; i++)
    {
        SDL_Rect currentRect;
        currentRect.x = (i % nbSpritesPerLine) * (size.x / nbSpritesPerLine);
        currentRect.y = (i / nbSpritesPerLine) * (size.y / nbSpritesPerColumn);
        currentRect.w = (size.x / nbSpritesPerColumn);
        currentRect.h = (size.y / nbSpritesPerColumn);

        tabRect[i] = currentRect;
    }

    // ******************************************************** //
    
    rectOnScreen = (SDL_Rect*)malloc(nbLin * nbCol * sizeof(SDL_Rect));

    int nbOfRectangles = nbLin * nbCol;

    for (int i = 0; i < nbOfRectangles; i++)
    {
        rectOnScreen[i] = {0, 0, 0, 0};
    }  

    int widthSprite = SCREEN_WIDTH / nbCol;
    int heightSprite = SCREEN_HEIGHT / nbLin;

    for (int i = 0; i < nbOfRectangles; i++) 
    {
        SDL_Rect currentRect;
        currentRect.x = (i % nbCol) * widthSprite;
        currentRect.y = (i / nbCol) * heightSprite;
        currentRect.w = widthSprite;
        currentRect.h = heightSprite;

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
            // Vérifie que i et j sont dans les limites
            if (i < nbLin && j < nbCol)
            {
                // Si on met des numéros non autorisés
                if (tab[i][j] >= 0 && tab[i][j] < nbSprites)
                {
                    SDL_Rect currentRect = tabRect[tab[i][j]];                    
                    SDL_RenderCopy(renderer, tilemap, &currentRect, &rectOnScreen[i * nbCol + j]);
                    
                    // Ca permet de créer un une colonne de plus à droite au cas-où 
                    if (j == nbCol - 1)
                    {
                        SDL_Rect additionalRect = rectOnScreen[i * nbCol + j];
                        additionalRect.x += rectOnScreen[i * nbCol + j].w;
                        SDL_RenderCopy(renderer, tilemap, &currentRect, &additionalRect);
                    }
                    // Ca permet de créer un une ligne  de plus en bas au cas-où 
                    if (i == nbLin - 1)
                    {
                        SDL_Rect additionalRect = rectOnScreen[i * nbCol + j];
                        additionalRect.y += rectOnScreen[i * nbCol + j].h;
                        SDL_RenderCopy(renderer, tilemap, &currentRect, &additionalRect);
                    }
                    // Ca permet de créer un tile tout en bas à droite au cas-où
                    if (i == nbLin - 1 && j == nbCol - 1)
                    {
                        SDL_Rect additionalRect = rectOnScreen[i * nbCol + j];
                        additionalRect.x += rectOnScreen[i * nbCol + j].w;
                        additionalRect.y += rectOnScreen[i * nbCol + j].h;
                        SDL_RenderCopy(renderer, tilemap, &currentRect, &additionalRect);
                    }
                }
            }
        }
    }
}

/**
 * @param file Le fichier ouvert avec fopen
 * Retourne dans Map.nbCol et Map.nbLin le nombre de lignes et de colonnes du fichier
*/
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

    if (nbLin == 0)
    {
        throw std::invalid_argument("Le fichier de la carte est vide");
    }

    nbCol = max_col;
}

/**
 * @param textFileName La source du fichier à ouvrir pour construire la map
 * Dans cette fonction, on appelle fileSize(file) pour récupérer le nombre de lignes et de colonne dans le fichier et on alloue le tableau.
*/
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

/**
 * Gestion d'allocation du tableau 2D
*/
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
