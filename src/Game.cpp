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

    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        exit(1);
    };

    this->player = new Player(100, 160.0f, 50, 50, 64, 64, renderer);
    // player->getAnimation()->createTextureFromSurface("assets/sprites/player.png", renderer, window);
    for (int i = 0; i < 5; i++)
    {
        addEnemy(SCREEN_WIDTH / 3 + 50 * i, SCREEN_HEIGHT / 2, 30, 30);
    }
    this->barHp = new Bar(10, 10, 100, 30, {255, 255, 0, 0});

    int SDL_EnableKeyRepeat(0);
    
    // this->enemies = new Enemy(20, 40.0f, 500, 500, 40, 40);
    this->equipement = new Equipement();
 
    mainMenu = new Menu(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    map = new Map("assets/map/map1.txt", "assets/sprites/tilemap.png", renderer);
}

void Game::renderGame()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    switch (currentState)
    {
        case MainMenu:
            mainMenu->render();
            break;
        case Settings:
            map->render(renderer);
            break;
        case Run:
        {
            map->render(renderer);
            this->player->render(renderer);
            if (this->equipement != nullptr)
            {
                this->equipement->render(renderer);
            }

            ennemies_t* currentEnemy = enemies;
            while (currentEnemy != nullptr && currentEnemy->val != nullptr)
            {
                Enemy* ennemi = currentEnemy->val;
                ennemi->render(renderer);
                currentEnemy = currentEnemy->next;
            }

            projectiles_t* currentProjectile = projectiles;
            while (currentProjectile != nullptr && currentProjectile->val != nullptr)
            {
                Projectile* projectile = currentProjectile->val;
                projectile->render(renderer);
                currentProjectile = currentProjectile->next;
            }

            barHp->render(renderer);
            break;
        }
        case GameOver:
        {       
            Text* g = new Text(renderer, 50, 150, 400, 300, {255, 255, 255, 255});
            g->setText("Game Over sale merde");
            g->render();
            break;
        }
        default:
            break;
    }

    SDL_RenderPresent(renderer);
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
                    case SDLK_o:
                        addEnemy(SCREEN_WIDTH / 3 + 200, SCREEN_HEIGHT / 2, 150, 150);
                        break;
                    case SDLK_h:
                        player->setHP(player->getHP() + 10);
                        break;
                    case SDLK_p:
                    {
                        if (enemies != nullptr)
                        {
                            float minDistance = 200000.f;
                            float currentDis = 0;
                            Enemy* enemyIndex;
                            ennemies_t* currentEnemy = enemies;
                            while (currentEnemy != nullptr && currentEnemy->val != nullptr)
                            {
                                Enemy* e = currentEnemy->val;
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
    double deltaTime, elapsedTime;
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

        elapsedTime += deltaTime;

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
            ennemies_t* currentEnemy = enemies;
            while (currentEnemy != nullptr && currentEnemy->val != nullptr)
            {
                Enemy* ennemi = currentEnemy->val;
                if (ennemi->collision(player) && elapsedTime >= 1.f)
                {
                    player->setHP(player->getHP() - 10);

                    // printf("%d", player->getHP());
                    elapsedTime = 0.f;
                }
                ennemi->behavior(player);
                ennemi->update(deltaTime);
                distanceEnemy = ennemi->distance(player);

                ennemi->render(renderer);
                currentEnemy = currentEnemy->next;
            }

            currentEnemy = enemies;
            while (currentEnemy != nullptr && currentEnemy->val != nullptr)
            {
                Enemy* enemy = currentEnemy->val;
                bool ennemyRemove = false;

                projectiles_t* currentProjectile = projectiles; 
                while (currentProjectile != nullptr && currentProjectile->val != nullptr)
                {
                    Projectile* proj = currentProjectile->val;
                    bool projectileRemoved = false;
                    proj->update(deltaTime);

                    if (enemy->collision(proj))
                    {
                        projectileRemoved = true;
                        ennemyRemove = true;

                        enemies = remove(enemies, enemy);
                        projectiles = remove(projectiles, proj);
                        break; 
                    }

                    if (!projectileRemoved)
                    {
                        currentProjectile = currentProjectile->next;
                    }
                    
                }

                if (!ennemyRemove)
                {
                    currentEnemy = currentEnemy->next;
                }
                
                
            }
            

            // projectiles_t* currentProjectile = projectiles;
            // while (currentProjectile != nullptr && currentProjectile->val != nullptr)
            // {
            //     Projectile* projectile = currentProjectile->val;
            //     if (projectile == nullptr)
            //         break;
            //     projectile->update(deltaTime);
            //     bool projectileRemoved = false;

            //     ennemies_t* currentEnemy = enemies;
            //     while (currentEnemy != nullptr && currentEnemy->val != nullptr)
            //     {
            //         Enemy* ennemi = currentEnemy->val;
            //         if (ennemi->collision(projectile))
            //         {
            //             projectileRemoved = true;

            //             enemies = remove(enemies, ennemi);
            //             projectiles = remove(projectiles, projectile);
            //             break; 
            //         }
            //         else
            //         {
            //             currentEnemy = currentEnemy->next;
            //         }
            //     }

            //     // Vérifier s'il faut avancer le pointeur des projectiles
            //     if (!projectileRemoved)
            //     {
            //         currentProjectile = currentProjectile->next;
            //     }

            //     // distanceEnemy = projectile->distance(player);
            //     projectile->render(renderer);
            // }

           if(equipement != nullptr && player->collision(equipement))
            {
               
                if(equipement != nullptr)
                    delete equipement;
                equipement = nullptr;
                
                player->setSpeed(player->getSpeed() * 2);
            }

            if(player->collision(barHp))
            {
                barHp->moveBar();
            }

            barHp->setWidth(player->getHP());

            if (player->getHP() <= 0)
            {
                currentState = GameOver;
            }
            
            break;
        }
        
        case Settings:
            break;
        case GameOver:
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
    ennemies_t* nouvelEnnemi = new ennemies_t;
    nouvelEnnemi->val = new Enemy(20, 40.0f, x, y, width, height, renderer);
    nouvelEnnemi->next = enemies;
    enemies = nouvelEnnemi;
}

void Game::shoot(float angle)
{
    projectiles_t* proj = new projectiles_t;
    proj->val = new Projectile(player->getX() + player->getWidth() / 2, player->getY() + player->getHeight() / 2, angle, 100.f);
    proj->next = projectiles;
    projectiles = proj;

    // projectiles_t* currentProjectile = projectiles;
    // while (currentProjectile != nullptr && currentProjectile->val != nullptr)
    // {
    //     Projectile* projectile = currentProjectile->val;
    //     if (currentProjectile->next == nullptr)
    //     {
    //         currentProjectile->next = proj;
    //         break;
    //     }
    // }

    
}


/**
 * TODO: Liste chainée par objets
 * TODO: Gérer le try & catch de la map
 * TODO: Vie et affichage de la vie
 * TODO: Si possible save & continue
*/
int main(int argc, char **argv)
{
    const std::string& title = "Jeu";
    game = new Game(title);
    game->update();

    delete game;

    return 0;
}