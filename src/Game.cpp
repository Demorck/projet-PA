#define SDL_MAIN_HANDLED
#include <Game.hpp>
#include <Constant.hpp>
#include <math.h>


Game* game;


Game::Game(const std::string& title)
    : title(title)
{
    this->isRuning = true;
    this->init();
}

Game::~Game()
{

}

/**
 * * Initialise le jeu avec les différents modules SDL
 * ? Les initialisations des joueurs et des ennemis seront enlevés quand on fera un menu et tout
*/
void Game::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->window == nullptr) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // int imgFlags = IMG_INIT_PNG;
    // if( !( IMG_Init( imgFlags ) & imgFlags ) )
    // {
    //     std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    //     exit(1);
    // }

    this->player = new Player(20, 160.0f, 50, 50, 40, 40);
    // player->getAnimation()->createTextureFromSurface("assets/sprites/player.png", renderer, window);
    for (int i = 0; i < 5; i++)
    {
        this->enemies.push_back(new Enemy(20, 40.0f, 500 + 50 * i, 500, 30, 30));
    }

    int SDL_EnableKeyRepeat(0);
    
    // this->enemies = new Enemy(20, 40.0f, 500, 500, 40, 40);
    this->equipement = new Equipement();

    mainMenu = new Menu(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::render()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);

    // this->player->render(this->renderer);
    // this->equipement->render(this->renderer);
    // for (int i = 0; i < this->enemies.size(); i++)
    // {
    //     this->enemies.at(i)->render(this->renderer);
    // }

    // for (Projectile* p : projectiles)
    // {
    //     p->render(renderer);
    // }

    mainMenu->render();
    
    
    // this->enemies->render(this->renderer);

    SDL_RenderPresent(this->renderer);
}

/**
 * * La boucle d'events. 
 * ! Tous les events à mettre ici
*/
void Game::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        
        switch (e.type)
        {
            case SDL_QUIT:
                isRuning = false;
                break;
            case SDL_KEYDOWN:
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_z:
                        player->move(UP, true);
                        player->move(DOWN, false);
                        break;
                    case SDLK_q:
                        player->move(LEFT, true);
                        player->move(RIGHT, false);
                        break;
                    case SDLK_s:
                        player->move(DOWN, true);
                        player->move(UP, false);
                        break;
                    case SDLK_d:
                        player->move(RIGHT, true);
                        player->move(LEFT, false);
                        break;
                    case SDLK_p:
                    {
                        float minDistance = 200000.f;
                        float currentDis = 0;
                        Enemy* enemyIndex;
                        for (Enemy* e : enemies)
                        {
                            currentDis = e->distance(player);
                            if (currentDis < minDistance)
                            {
                                minDistance = currentDis;
                                enemyIndex = e;
                            }
                        }
                        float angle = atan2(enemyIndex->getY() - this->player->getY(), enemyIndex->getX() - this->player->getX()); 
                        this->projectiles.push_back(std::move(new Projectile(this->player->getX(), player->getY(), angle, 200.0f)));
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case SDL_KEYUP:
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_z:
                    if (player->isMoving(UP))
                        player->move(UP, false);
                    break;
                case SDLK_q:
                    if (player->isMoving(LEFT))
                        player->move(LEFT, false);
                    break;
                case SDLK_s:
                    if (player->isMoving(DOWN))
                        player->move(DOWN, false);
                    break;
                case SDLK_d:
                    if (player->isMoving(RIGHT))
                        player->move(RIGHT, false);
                    break;
                
                default:
                    break;
                }
            }
            default:
                break;
        }

    }
    
    // this->player->handleEvents();
}

void Game::update()
{
    Uint32 currentTime, lastTime = SDL_GetTicks();
    double deltaTime;
    Enemy* closestEnemy;
    float distanceEnemy;
    float minDistance;

    while (this->isRuning)
    {
        currentTime = SDL_GetTicks();
        deltaTime = (double)(currentTime - lastTime) / 1000.0;
        lastTime = currentTime;        

        this->player->update(deltaTime);
        minDistance = 200000.0f;
        // for (Enemy* enemy : enemies)
        // {
        //     if (enemy->collision(player))
        //     {
        //         enemies.erase(enemies.begin());
        //         enemies.push_back(new Enemy(20, 60.0f, 500, 500, 30, 30));

        //     }
        //     enemy->behavior(player);
        //     enemy->update(deltaTime);
        //     distanceEnemy = enemy->distance(player);
        // }

        // for (auto i = projectiles.begin(); i != projectiles.end(); i++)
        // {
        //     auto it1 = std::next(projectiles.begin(), 2);
        //     for (auto j = enemies.begin(); j != enemies.end(); j++)
        //     {
        //         if ((*j)->collision((*it1)))
        //         {
        //             this->enemies.erase(j);
        //             projectiles.erase(it1);
                    
        //             // this->enemies.push_back(new Enemy(20, 60.0f, 500, 500, 30, 30));

        //         }
        //     }
        
        //     (*it1)->update(deltaTime);
        // }

        // if (player->collision(equipement))
        // {
        //     delete equipement;
        //     player->setSpeed(player->getSpeed() * 2);
        // }

        mainMenu->update(deltaTime);
        
        this->handleEvents();
        this->render();                                             
    }    
    if(player->collision(equipement)){
        delete equipement;
        player->setSpeed(2.0);
    }
}

int main(int argc, char **argv)
{
    const std::string& title = "Jeu";
    game = new Game(title);
    game->update();

    return 0;
}