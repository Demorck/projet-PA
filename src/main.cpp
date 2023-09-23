#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include "Constant.hpp"

const std::string& title = "Jeu";
SDL_Renderer* renderer;
SDL_Window* window;
bool quit = false;
 
void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void handleEvents()
{
    
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
         switch (event.type)
         {
            case SDL_QUIT:
                quit = true;
                
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_r:
                    std::cout << "R key pressed" << std::endl;
                    break;
                case SDLK_SPACE:
                    std::cout << "Space key pressed" << std::endl;
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                default:
                    break;
                }
                break;
        }
    }
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_Rect rect = {50, 50, 40, 40};   
    SDL_SetRenderDrawColor(renderer, 250, 20, 20, 0);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    init();
    while (!quit) {
        handleEvents();
        render();
    }

    return 0;
}