#include <SDL2/SDL.h>
#include <iostream>
 
int WinMain(int argc, char **argv)
{
 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("GAME",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1080, 720, 0);
    
    while(1);
 
    return 0;
}