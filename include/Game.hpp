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
        bool canContinue;
        const std::string& title;
        int savescore =1;
        
        Player* player = nullptr;
        
        int score;
        Text* scoreRender = nullptr;
        Text* g = nullptr;
        Menu* mainMenu = nullptr;
        Map* map = nullptr;
        Bar* barHp = nullptr;

        ennemies_t* enemies = nullptr;
        projectiles_t* projectiles = nullptr;
        equipements_t* equipements = nullptr;

        int waveNumber = 0;
        double timeSinceLastWave;
        double timeBetweenWaves = 5.f;

        State currentState;

        void addEnemy(float x, float y, int width, int height);
        void addEquipement(int type, SDL_Color couleur);
        void startNextWave();
        void shoot(float angle);


        void newGame();
        void saveGame();
        void loadGame();
        void saveBestScore();


};



#endif