#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <UI/Menu.hpp>
#include <Player.hpp>
#include <Enemy.hpp>
#include <Equipement.hpp>
#include <Projectile.hpp>
// #include <Helpers/Animation.hpp>

enum STATE {MainMenu, Settings, Exit, Run};

class Game
{
    public:
        Game(const std::string& title);
        void handleEvents();
        void init();
        void render();
        void update();
        ~Game();

    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        bool isRuning;
        const std::string& title;
        
        Player* player;
        std::vector<Enemy*> enemies;
        Enemy* enemy;
        Equipement* equipement;
        std::list<Projectile*> projectiles;
        Menu* mainMenu;

};



#endif