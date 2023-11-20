#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <Player.hpp>
#include <Enemy.hpp>
#include <Equipement.hpp>
#include <Projectile.hpp>
// #include <Helpers/Animation.hpp>
#include <Helpers/Enums.hpp>
#include <UI/Menu.hpp>
#include <UI/Render.hpp>
#include <Map.hpp>
#include <Helpers/Struct.hpp>

class Game
{
    public:
        Game(const std::string& title);
        void handleEvents();
        void init();
        void renderGame();
        void update();
        ~Game();

    private:
        Render& render = Render::getInstance();
        bool isRuning;
        const std::string& title;
        
        Player* player;
        // std::vector<Enemy*> enemies;
        Equipement* equipement;
        // std::vector<Projectile*> projectiles;
        Menu* mainMenu;
        Map* map;

        list_t* enemies;
        list_t* projectiles;

        State currentState;

        void addEnemy(float x, float y, int width, int height);
        void shoot(float angle);

};



#endif