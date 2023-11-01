#define SDL_MAIN_HANDLED
#include <Game.hpp>
#include <Constant.hpp>


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
        this->enemies.push_back(new Enemy(20, 40.0f, 500 + 50 * i, 500, 40, 40));
    }
    
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
    
    // this->enemies->render(this->renderer);

    SDL_RenderPresent(this->renderer);
}

void Game::handleEvents()
{
    this->player->handleEvents();
}

void Game::update()
{
    Uint32 currentTime, lastTime = SDL_GetTicks();
    double deltaTime;

    while (this->isRuning)
    {
        currentTime = SDL_GetTicks();
        deltaTime = (double)(currentTime - lastTime) / 1000.0;
        lastTime = currentTime;        

        this->player->update(deltaTime);
        for (int i = 0; i < this->enemies.size(); i++)
        {
            if (this->enemies.at(i)->collision(this->player))
            {
                this->enemies.erase(this->enemies.begin());
                this->enemies.push_back(new Enemy(20, 60.0f, 500, 500, 30, 30));

            }
            this->enemies.at(i)->behavior(this->player);
            this->enemies.at(i)->update(deltaTime);
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