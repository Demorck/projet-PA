#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include "Constant.hpp"
#include <Player.hpp>
#include <Enemy.hpp>
#include <Equipement.hpp>

const std::string& title = "Jeu";
SDL_Renderer* renderer;
SDL_Window* window;
Player* player;
Enemy* enemy;
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
    enemy->render(renderer);

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{

    player = new Player(30, 100.0f, 20, 20);
    enemy = new Enemy(20, 60.0f, 160, 160);
    init();

    Uint32 currentTime, lastTime = SDL_GetTicks();
    double deltaTime;

    Equip = new Equipement();

    while (!quit) {
        currentTime = SDL_GetTicks();
        deltaTime = (double)(currentTime - lastTime) / 1000.0;
        lastTime = currentTime;

        handleEvents();
        player->update(deltaTime);
        enemy->behavior(player);
        enemy->update(deltaTime);
        render();

    }

    return 0;
}