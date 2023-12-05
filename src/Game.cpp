#define SDL_MAIN_HANDLED
#include <Game.hpp>
#include <Constant.hpp>
#include <math.h>
#include <fstream>
#include <random>
#include <time.h>

Game* game;


Game::Game(const std::string& title)
    : title(title), enemies(nullptr), projectiles(nullptr)
{
    this->isRuning = true;
    this->init();
    
    currentState = MainMenu;
    canContinue = true;
}

Game::~Game()
{
    if (mainMenu != nullptr)
        delete mainMenu;

    if (player != nullptr) 
        delete player;

    if (map != nullptr)
        delete map;
    
    if (barHp != nullptr)
        delete barHp;
    
    if (scoreRender != nullptr)
        delete scoreRender;
    
    if (enemies != nullptr)
        freeList(enemies);

    if (projectiles != nullptr)
        freeList(projectiles);

    if (equipements != nullptr)
        freeList(equipements);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
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

    mainMenu = new Menu(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    /*Initialisation du joueur*/
    this->player = new Player(HP_PLAYER, SPEED_PLAYER, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, WIDTH_PLAYER, HEIGHT_PLAYER, renderer);
    loadGame();    
    
}

void Game::newGame()
{
    if (player != nullptr)
    {
        delete player;
        player = nullptr;
    }
    if (enemies != nullptr)
    {
        freeList(enemies);
        enemies = nullptr;
    }
    if (map != nullptr)
    {
        delete map;
        map = nullptr;
    }
    if (barHp != nullptr)
    {
        delete barHp;
        barHp = nullptr;
    }
    if (projectiles != nullptr)
    {
        freeList(projectiles);
        projectiles = nullptr;
    }
    if (equipements != nullptr)
    {
        freeList(equipements);
        equipements = nullptr;
    }
    /*Génération d'un joueur quand on lance une game  */
    this->player = new Player(HP_PLAYER, SPEED_PLAYER, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, WIDTH_PLAYER, HEIGHT_PLAYER, renderer);
    for (int i = 0; i < 5; i++)
    {
        addEnemy(SCREEN_WIDTH / 3 + 50 * i, SCREEN_HEIGHT / 2, 30, 30);
    }
    /*Génération de la bar d'hp pour la nouvelle partie*/
    this->barHp = new Bar(CORD_X_BAR_HP, CORD_Y_BAR_HP, WIDTH_X_BAR_HP, HEIGHT_Y_BAR_HP, COUL_BAR_HP);

    int SDL_EnableKeyRepeat(0);
    
    
    for (int i = 0; i < 3; i++) 
    {
        SDL_Color coult = {i*50,i*75,i*100,i*125};
        addEquipement(i,coult);
    }

    /*initialisation du score et de son affichage*/
    this->score = 0;
    this->scoreRender = new Text(renderer, SCREEN_WIDTH-(TAILLE_SCORE), SCREEN_HEIGHT-(TAILLE_SCORE),TAILLE_SCORE, TAILLE_SCORE, {255, 255, 255, 255});
    std::string chaine = std::to_string(this->score);
    this->scoreRender->setText(chaine);


    try
    {
        map = new Map("assets/map/map1.txt", "assets/sprites/tilemap.png", renderer);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

void Game::renderGame()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    switch (currentState)
    {
        case MainMenu:
            mainMenu->render(canContinue);
            break;
        case Settings:
            map->render(renderer);
            break;
        case Run:
        {
            map->render(renderer);
            this->player->render(renderer);
            
            this->scoreRender = new Text(renderer, SCREEN_WIDTH-(TAILLE_SCORE), SCREEN_HEIGHT-(TAILLE_SCORE),TAILLE_SCORE, TAILLE_SCORE, {255, 255, 255, 255});
            std::string chaine = std::to_string(this->score);
            this->scoreRender->setText(chaine);
            this->scoreRender->render();

            equipements_t* currentEquipement = equipements; 
            while(currentEquipement != nullptr){
                Equipement* equipement = currentEquipement->val;
                equipement->render(renderer);
                currentEquipement = currentEquipement->next;
            }

            ennemies_t* currentEnemy = enemies;
            while (currentEnemy != nullptr)
            {
                Enemy* ennemi = currentEnemy->val;
                ennemi->render(renderer);
                currentEnemy = currentEnemy->next;
            }

            projectiles_t* currentProjectile = projectiles;
            while (currentProjectile != nullptr)
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
            g->setText("Game Over :((");
            g->render();
            this->saveBestScore();
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
                    case SDLK_e:/*commande de debugage pour ajouter des equipement */
                        addEquipement(1,COUL_PAR_DEF);
                        break;
                    case SDLK_o:/*commande de debugage pour ajouter des ennemy*/
                        addEnemy(SCREEN_WIDTH / 3 + 200, SCREEN_HEIGHT / 2, WIDTH_X_ENNEMY, HEIGHT_Y_ENNEMY);
                        break;
                    case SDLK_h:/*commande de debugage pour ajouter de la vie*/
                        player->setHP(player->getHP() + AJOUT_HP);
                        break;
                    case SDLK_n:
                        saveGame();
                        break;
                    case SDLK_b:
                        loadGame();
                        break;
                        //
                    case SDLK_p:
                    {
                        if (enemies != nullptr)
                        {
                            float minDistance = SCREEN_WIDTH;
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
                        if (currentState == Run or currentState == Settings or currentState == GameOver or currentState == Continue)
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
    
    
}

void Game::update()
{
    Uint32 currentTime, lastTime = SDL_GetTicks();
    double deltaTime, elapsedTime = 0.f;
    Enemy* closestEnemy;
    float distanceEnemy;
    float minDistance;

    while (this->isRuning)
    {
        currentTime = SDL_GetTicks();
        deltaTime = (double)(currentTime - lastTime) / 1000.0;
        lastTime = currentTime;        

        minDistance = 200000.0f;

        elapsedTime += deltaTime;

        switch (currentState)
        {
        case MainMenu:
            mainMenu->update(deltaTime, currentState);
            break;
        
        case NewGame:
            currentState = Run;
            newGame();
            break;

        case Run:
        {
            
            this->player->update(deltaTime);

            ennemies_t* currentEnemy = enemies;
            while (currentEnemy != nullptr && currentEnemy->val != nullptr)
            {
                Enemy* ennemi = currentEnemy->val;
                if (ennemi->collision(player) && elapsedTime >= .5f)
                {
                    this->score = this->score -2;
                    
                    player->setHP(player->getHP() - 10);
                    elapsedTime = 0.f;
                }

                ennemi->behavior(player);
                ennemi->update(deltaTime);
                distanceEnemy = ennemi->distance(player);

                currentEnemy = currentEnemy->next;
            }

            currentEnemy = enemies;
            while (currentEnemy != nullptr)
            {
                Enemy* enemy = currentEnemy->val;
                bool ennemyRemove = false;

                projectiles_t* currentProjectile = projectiles; 
                while (currentProjectile != nullptr)
                {
                    Projectile* proj = currentProjectile->val;
                    bool projectileRemoved = false;

                    if (enemy->collision(proj))
                    {
                        projectileRemoved = true;
                        ennemyRemove = true;

                        enemies = remove(enemies, enemy);
                        projectiles = remove(projectiles, proj);
                        this->score = this->score + 5;
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
                else
                {
                    currentEnemy = enemies;
                }
                
            }

            projectiles_t* currentProjectile = projectiles;
            while (currentProjectile != nullptr)
            {
                Projectile* projectile = currentProjectile->val;
                projectile->update(deltaTime);
                currentProjectile = currentProjectile->next;
            }

            equipements_t* currentstrucEquipement = equipements;
            while(currentstrucEquipement != nullptr){
                bool equipementRemoved = false;
                Equipement* currentEquipement = currentstrucEquipement->val;
                if(player->collision(currentEquipement)){
                    
                    if(currentEquipement->getType() == 0){
                        player->setSpeed(player->getSpeed() * 2);
                    }
                    if(currentEquipement->getType() == 1){
                        player->setHP(player->getHP() + 5);
                    }
                    if(currentEquipement->getType() == 2){
                        this->score = this->score +10;
                        int j = this->score;
                        
                    }

                    equipementRemoved = true;
                    equipements = remove(equipements, currentEquipement);
                
                }
                
                if (!equipementRemoved)
                {
                    currentstrucEquipement = currentstrucEquipement->next;
                }
                else
                {
                    currentstrucEquipement = equipements;
                }
            }

            if(player->collision(barHp))
            {
                barHp->moveBar();
            }

            barHp->setWidth(player->getHP());

            if (player->getHP() <= 0)
            {
                currentState = GameOver;
                canContinue = false;
            }
            
            break;
        }
        
        case Settings:
            break;
        case GameOver:
            break;
        case Exit:
            this->isRuning = false;
            break;
        case Continue:
            newGame();
            loadGame();
            currentState = Run;
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

void Game::addEquipement(int typ, SDL_Color couleur)
{
    equipements_t* nouveauEquipement = new equipements_t;
    nouveauEquipement->val = new Equipement(typ,couleur);
    nouveauEquipement->next = equipements;
    equipements = nouveauEquipement;
}

void Game::shoot(float angle)
{
    projectiles_t* proj = new projectiles_t;
    proj->val = new Projectile(player->getX() + player->getWidth() / 2, player->getY() + player->getHeight() / 2, angle, 100.f);
    proj->next = projectiles;
    projectiles = proj;    
}



void Game::saveBestScore(){
    std::string filename = "bestScore.dat";

    std::ifstream fichier(filename, std::ios::binary);
    if (fichier.good()) {
        
            int tableauEntiers[4];
            int nombre;
            int index = 0;
            
            while (fichier >> nombre && index < 4) {
                
                tableauEntiers[index++] = nombre;
            }

            int scoreT = this->score; 

            for(int i = 0; i < index; i++){
                if(tableauEntiers[i]<scoreT){
                    tableauEntiers[i] = scoreT;
                }
            }
            fichier.close();

            std::ofstream file(filename);

            if(file.is_open()){

                for (int i = 0; i < index; ++i) {
                    file << tableauEntiers[i] << " ";
                }
                file.close();
            } else {
                std::cerr << "Impossible d'ouvrir le fichier pour l'écriture : " << filename << std::endl;
            }
    } else {
        std::ofstream file(filename, std::ios::binary);

        if (file.is_open())
        {
        
            file.write(reinterpret_cast<const char*>(&score), sizeof(score));

            file.close();
        }
        else {
            
            std::cerr << "Unable to open file for writing: " << filename << std::endl;
    
            }
    }
}

void Game::saveGame()
{
    std::string filename = "save.dat";
    std::ofstream file(filename, std::ios::out | std::ios::binary);

    if (file.is_open())
    {
        file.write(reinterpret_cast<const char*>(&canContinue), sizeof(canContinue));
        player->save(file);
        file.write(reinterpret_cast<const char*>(&score), sizeof(score));

        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

void Game::loadGame()
{
    std::string filename = "save.dat";
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (file.is_open())
    {
        file.read(reinterpret_cast<char*>(&canContinue), sizeof(canContinue));
        player->load(file);
        file.read(reinterpret_cast<char*>(&score), sizeof(score));

        file.close();
    }
    else
    {
        canContinue = false;
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
}


/**
 * TODO: Modifier le fichier de sauvegarde quand on meurt
 * TODO: Caractères non autorisés
 * TODO: Version jouable
 * TODO: Fichier texte crash
 * TODO: Constantes
 * TODO: Commentaires
 * TODO: Valgrind
 * TODO: Class texte
 * TODO: Les trucs violets quand on make
*/
int main(int argc, char **argv)
{
    srand(time(NULL));
    const std::string& title = "Jeu";
    game = new Game(title);
    game->update();
    delete game;

    return 0;
}