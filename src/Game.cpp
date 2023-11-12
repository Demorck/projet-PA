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
    currentState = MainMenu;
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

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init error: " << TTF_GetError() << std::endl;
        exit(1);
    }

    this->player = new Player(20, 160.0f, 50, 50, 64, 64);
    // player->getAnimation()->createTextureFromSurface("assets/sprites/player.png", renderer, window);
    for (int i = 0; i < 5; i++)
    {
        this->enemies.push_back(new Enemy(20, 40.0f, 500 + 50 * i, 500, 30, 30));
    }

    int SDL_EnableKeyRepeat(0);
    
    // this->enemies = new Enemy(20, 40.0f, 500, 500, 40, 40);
    this->equipement = new Equipement();

    mainMenu = new Menu(render.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
    map = new Map("assets/map/map1.txt", "assets/sprites/tilemap.png", render.getWindow(), render.getRenderer());
}

void Game::renderGame()
{
    SDL_SetRenderDrawColor(render.getRenderer(), 0, 0, 0, 0);
    SDL_RenderClear(render.getRenderer());

    switch (currentState)
    {
    case MainMenu:
        mainMenu->render();
        break;
    case Settings:
        map->render(render.getRenderer());
        break;
    case Run:
        this->player->render(render.getRenderer());
        this->equipement->render(render.getRenderer());
        for (int i = 0; i < this->enemies.size(); i++)
        {
            this->enemies.at(i)->render(render.getRenderer());
        }

        for (Projectile* p : projectiles)
        {
            p->render(render.getRenderer());
        }
    default:
        break;
    }

    SDL_RenderPresent(render.getRenderer());
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
        mainMenu->handleEvents(e);
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
                        if (enemies.size() > 0)
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
                            this->projectiles.push_back(new Projectile(player->getX() + player->getWidth() / 2, player->getY() + player->getHeight() / 2, angle, 200.0f));
                        }
                        break;
                    }
                    case SDLK_ESCAPE:
                    {
                        if (currentState == Run or currentState == Settings)
                        {
                            currentState = MainMenu;
                        }
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

        switch (currentState)
        {
        case MainMenu:
            mainMenu->update(deltaTime, currentState);
            break;

        case Run:
        {
            /**
             * ! A modifier pour que ça fasse des dégâts au joueur
            */
            for (Enemy* enemy : enemies)
            {
                if (enemy->collision(player))
                {
                    enemies.erase(enemies.begin());
                    enemies.push_back(new Enemy(20, 60.0f, 500, 500, 30, 30));

                }
                enemy->behavior(player);
                enemy->update(deltaTime);
                distanceEnemy = enemy->distance(player);
            }

            /**
             * Si un projectile touche un ennemi.
             * ! Pour le moment, ça enlève l'ennemi. A terme, ça doit enlever de la vie.
            */
            for (auto i = projectiles.begin(); i != projectiles.end();)
            {
                (*i)->update(deltaTime);

                bool projectileRemoved = false;

                for (auto j = enemies.begin(); j != enemies.end();)
                {
                    if ((*j)->collision(*i))
                    {
                        delete *j;
                        j = enemies.erase(j);

                        delete *i;
                        i = projectiles.erase(i);

                        projectileRemoved = true;
                        break;  
                    }
                    else
                    {
                        ++j;
                    }
                }

                // Si un projectile n'est pas enlevé, incrémente l'itérateur car erase renvoie le prochain dans std::vector
                if (!projectileRemoved)
                {
                    ++i;
                }
            }

            if (player->collision(equipement))
            {
                delete equipement;
                player->setSpeed(player->getSpeed() * 2);
            }
            break;
        }
        
        case Settings:
            break;
        default:
            break;
        }
        
        this->handleEvents();
        this->renderGame();                                             
    }    
   
}

int main(int argc, char **argv)
{
    const std::string& title = "Jeu";
    game = new Game(title);
    game->update();

    return 0;
}