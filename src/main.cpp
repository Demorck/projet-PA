#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include "Constant.hpp"
#include <Entity.hpp>
#include <Equipement.hpp>

const std::string& title = "Jeu";
SDL_Renderer* renderer;
SDL_Window* window;
Entity* player;
Equipement* Equip;
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
    player->handleEvents();
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    player->render(renderer);
    Equip->render(renderer);

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    
    int LAST_UPDATE_TIME = SDL_GetTicks();

    player = new Entity(30, 100.0f, 20, 20);
    init();
    Uint32 currentTime, lastTime = SDL_GetTicks();
    double deltaTime;

    Equip = new Equipement();

    while (!quit) {
        currentTime = SDL_GetTicks();
        deltaTime = (double)(currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        player->handleEvents();
        player->update(deltaTime);
        render();
    }

    return 0;
}