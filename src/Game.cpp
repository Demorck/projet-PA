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

    this->player = new Player(20, 80.0f, 50, 50, 40, 40);
    for (int i = 0; i < 5; i++)
    {
        this->enemies.push_back(new Enemy(20, 40.0f, 500 + 50 * i, 500, 30, 30));
    }

    int SDL_EnableKeyRepeat(0);
    
    // this->enemies = new Enemy(20, 40.0f, 500, 500, 40, 40);
    this->equipement = new Equipement();
}

void Game::render()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);

    this->player->render(this->renderer);
    this->equipement->render(this->renderer);
    for (int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies.at(i)->render(this->renderer);
    }

    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles.at(i)->render(this->renderer);
    }
    
    // this->enemies->render(this->renderer);

    SDL_RenderPresent(this->renderer);
}

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
                        int enemyIndex;
                        for (int i = 0; i < this->enemies.size(); i++)
                        {
                            currentDis = this->enemies.at(i)->distance(player);
                            if (currentDis < minDistance)
                            {
                                minDistance = currentDis;
                                enemyIndex = i;
                            }
                        }
                        float angle = atan2(this->enemies.at(enemyIndex)->getY() - this->player->getY(), this->enemies.at(enemyIndex)->getX() - this->player->getX()); 
                        this->projectiles.push_back(new Projectile(this->player->getX(), player->getY(), angle, 200.0f));
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
                    {
                        std::cout << "a" << std::endl;
                        player->move(UP, false);
                    }
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
        for (int i = 0; i < this->enemies.size(); i++)
        {
            if (this->enemies.at(i)->collision(this->player))
            {
                this->enemies.erase(this->enemies.begin());
                this->enemies.push_back(new Enemy(20, 60.0f, 500, 500, 30, 30));

            }
            this->enemies.at(i)->behavior(this->player);
            this->enemies.at(i)->update(deltaTime);
            distanceEnemy = this->enemies.at(i)->distance(player);
        }

        for (int i = 0; i < projectiles.size(); i++)
        {
            projectiles.at(i)->update(deltaTime);
        }
         if(player->collision(equipement)){
        delete equipement;
        player->setSpeed(player->getSpeed()*2);
        }

        this->handleEvents();
        this->render();                                             
    }    
   
}

int main(int argc, char **argv)
{
    const std::string& title = "Jeu";
    game = new Game(title);
    game->update();

    return 0;
}