#define SDL_MAIN_HANDLED
#include <Game.hpp>
#include <Constant.hpp>
#include <math.h>


Game* game;


Game::Game(const std::string& title)
    : title(title), enemies(nullptr), projectiles(nullptr)
{
    this->isRuning = true;
    this->init();
    currentState = MainMenu;
}

Game::~Game()
{
    freeList(enemies);
    freeList(projectiles);
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
        addEnemy(SCREEN_WIDTH / 3 + 50 * i, SCREEN_HEIGHT / 2, 30, 30);
    }

    int SDL_EnableKeyRepeat(0);
    
    // this->enemies = new Enemy(20, 40.0f, 500, 500, 40, 40);
    this->equipement = new Equipement();

    mainMenu = new Menu(render.getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
    map = new Map("assets/map/map1.txt", "assets/sprites/tilemap.png", render.getRenderer());
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
        // map->render(render.getRenderer());
        break;
    case Run:
    {
        map->render(render.getRenderer());
        this->player->render(render.getRenderer());
        this->equipement->render(render.getRenderer());

        list_t* currentEnemy = enemies;
        while (currentEnemy != nullptr && currentEnemy->val != nullptr)
        {
            Enemy* ennemi = static_cast<Enemy*>(currentEnemy->val);
            ennemi->render(render.getRenderer());
            currentEnemy = currentEnemy->next;
        }

        list_t* currentProjectile = projectiles;
        while (currentProjectile != nullptr && currentProjectile->val != nullptr)
        {
            Projectile* projectile = static_cast<Projectile*>(currentProjectile->val);
            projectile->render(render.getRenderer());
            currentProjectile = currentProjectile->next;
        }
        break;
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
                    case SDLK_e:
                        this->player->setSpeed(160.f);
                        this->equipement = new Equipement();
                        break;
                    case SDLK_p:
                    {
                        if (enemies != nullptr)
                        {
                            float minDistance = 200000.f;
                            float currentDis = 0;
                            Enemy* enemyIndex;
                            list_t* currentEnemy = enemies;
                            while (currentEnemy != nullptr && currentEnemy->val != nullptr)
                            {
                                Enemy* e = static_cast<Enemy*>(currentEnemy->val);
                                currentDis = e->distance(player);
                                if (currentDis < minDistance)
                                {
                                    minDistance = currentDis;
                                    enemyIndex = e;
                                }
                                currentEnemy = currentEnemy->next;
                            }
                            float angle = atan2(enemyIndex->getY() - this->player->getY(), enemyIndex->getX() - this->player->getX()); 
                            shoot(angle);
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
            list_t* currentEnemy = enemies;
            while (currentEnemy != nullptr && currentEnemy->val != nullptr)
            {
                Enemy* ennemi = static_cast<Enemy*>(currentEnemy->val);
                // if (ennemi->collision(player))
                // {
                //     enemies.erase(enemies.begin());
                //     enemies.push_back(new Enemy(20, 60.0f, 500, 500, 30, 30));
                // }
                ennemi->behavior(player);
                ennemi->update(deltaTime);
                distanceEnemy = ennemi->distance(player);

                ennemi->render(render.getRenderer());
                currentEnemy = currentEnemy->next;
            }

            list_t* currentProjectile = projectiles;
            while (currentProjectile != nullptr && currentProjectile->val != nullptr)
            {
                Projectile* projectile = static_cast<Projectile*>(currentProjectile->val);
                projectile->update(deltaTime);
                bool projectileRemoved = false;

                list_t* currentEnemy = enemies;
                while (currentEnemy != nullptr && currentEnemy->val != nullptr)
                {
                    Enemy* ennemi = static_cast<Enemy*>(currentEnemy->val);
                    if (ennemi->collision(projectile))
                    {
                        projectileRemoved = true;

                        enemies = remove(enemies, currentEnemy);
                        projectiles = remove(projectiles, currentProjectile);
                        break; 
                    }
                    else
                    {
                        currentEnemy = currentEnemy->next;
                    }
                }

                // Vérifiez s'il faut avancer le pointeur des projectiles
                if (!projectileRemoved)
                {
                    currentProjectile = currentProjectile->next;
                }

                // distanceEnemy = projectile->distance(player);
                projectile->render(render.getRenderer());
            }

            /**
             * Si un projectile touche un ennemi.
             * ! Pour le moment, ça enlève l'ennemi. A terme, ça doit enlever de la vie.
            */
            // for (auto i = projectiles.begin(); i != projectiles.end();)
            // {
            //     (*i)->update(deltaTime);

            //     bool projectileRemoved = false;

            //     for (auto j = enemies.begin(); j != enemies.end();)
            //     {
            //         if ((*j)->collision(*i))
            //         {
            //             delete *j;
            //             j = enemies.erase(j);

            //             delete *i;
            //             i = projectiles.erase(i);

            //             projectileRemoved = true;
            //             break;  
            //         }
            //         else
            //         {
            //             ++j;
            //         }
            //     }

                // Si un projectile n'est pas enlevé, incrémente l'itérateur car erase renvoie le prochain dans std::vector
                // if (!projectileRemoved)
                // {
                //     ++i;
                // }
            // }

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

 void Game::addEnemy(float x, float y, int width, int height)
 {

    list_t* nouvelEnnemi = new list_t;
    nouvelEnnemi->val = new Enemy(20, 40.0f, x, y, width, height);
    nouvelEnnemi->next = enemies;
    enemies = nouvelEnnemi;
 }

 void Game::shoot(float angle)
 {
    list_t* proj = new list_t;
    proj->val = new Projectile(player->getX() + player->getWidth() / 2, player->getY() + player->getHeight() / 2, angle, 100.f);
    proj->next = projectiles;
    projectiles = proj;
 }

int main(int argc, char **argv)
{
    const std::string& title = "Jeu";
    game = new Game(title);
    game->update();
    delete game;

    return 0;
}