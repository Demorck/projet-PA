#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include "Constant.hpp"
#include <Entity.hpp>

const std::string& title = "Jeu";
SDL_Renderer* renderer;
SDL_Window* window;
Entity* player;
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

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    
    int LAST_UPDATE_TIME = SDL_GetTicks();

    player = new Entity(30, 100.0f, 20, 20);
    init();
    while (!quit) {
        // std::cout << deltaTime << std::endl;
        

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = ( CURRENT_TIME_MS - LAST_UPDATE_TIME ) * 0.01f;
        player->setSpeed(player->getSpeed() * std::min(ELAPSED_TIME_MS, 5 * 1000/50));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        std::cout << player->getSpeed() << std::endl;

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_q:
                        
                        player->setX(player->getX() * player->getSpeed() * ELAPSED_TIME_MS);
                        break;
                    case SDLK_z:
                        player->setY(player->getY() * player->getSpeed() * ELAPSED_TIME_MS);
                        break;
                    case SDLK_d:
                        player->setX(player->getX() * player->getSpeed() * ELAPSED_TIME_MS);
                        break;
                    case SDLK_s:
                        player->setY(player->getY() * player->getSpeed() * ELAPSED_TIME_MS);
                        break;
                    default:
                        break;
                    }
                    break;
            }
        }

        render();
        player->update();
    }

    return 0;
}