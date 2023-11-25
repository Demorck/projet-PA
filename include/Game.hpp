#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include <Helpers/Enums.hpp>
#include <Helpers/Struct.hpp>

#include <Player.hpp>
#include <Enemy.hpp>
#include <Equipement.hpp>
#include <Projectile.hpp>
#include <Map.hpp>

#include <UI/Menu.hpp>
#include <UI/Bar.hpp>

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
        SDL_Renderer* renderer;
        SDL_Window* window;
        bool isRuning;
        const std::string& title;
        
        Player* player;
        
        Menu* mainMenu;
        Map* map;
        Bar* barHp;

        ennemies_t* enemies = nullptr;
        projectiles_t* projectiles = nullptr;
        equipements_t* equipements = nullptr;

        State currentState;

        void addEnemy(float x, float y, int width, int height);
        void addEquipement(int typ, SDL_Color couleur);
        void shoot(float angle);

};



#endif