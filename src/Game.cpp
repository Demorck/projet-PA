#define SDL_MAIN_HANDLED
#include <Game.hpp>
#include <Constant.hpp>
#include <math.h>
#include <fstream>
#include <random>
#include <time.h>

Game* game;

/**
 * @param title : Le titre de la fenêtre
 * 
 * @brief Initialise le jeu et met l'état sur le menu principal. Par défaut, on peut continuer le jeu.
*/
Game::Game(const std::string& title)
    : title(title), score(0)
{
    this->isRuning = true;
    canContinue = true;
    this->init();
    
    currentState = MainMenu;
}

/**
 * @brief Détruit les objets correspondant et vérifie avant qu'on puisse les détruire
*/
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

    if (g != nullptr)
        delete g;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

/**
 * @brief Initialise SDL, TTF, la fenêtre et le renderer
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
    
    g = new Text(renderer, 50, 150, 400, 40, {255, 255, 255, 255});

    /* Initialisation du joueur */
    this->player = new Player(HP_PLAYER, SPEED_PLAYER, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, WIDTH_PLAYER, HEIGHT_PLAYER, renderer);
    loadGame();    
    
}

/**
 * @brief Réinitialise tous les états quand on lance une nouvelle partie.
*/
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

    if (scoreRender != nullptr)
        delete scoreRender;

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

    /* Génération d'un joueur quand on lance une partie  */
    this->player = new Player(HP_PLAYER, SPEED_PLAYER, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, WIDTH_PLAYER, HEIGHT_PLAYER, renderer);


    /* Génération de la bar d'hp pour la nouvelle partie */
    this->barHp = new Bar(CORD_X_BAR_HP, CORD_Y_BAR_HP, WIDTH_BAR_HP, HEIGHT_Y_BAR_HP, COUL_BAR_HP);
    
    
    for (int i = 0; i < 3; i++) 
    {
        SDL_Color coult = {(Uint8)(i*50), (Uint8)(i*75), (Uint8)(i*100), (Uint8)(i*125)};
        addEquipement(i,coult);
    }

    /*initialisation du score et de son affichage*/
    this->score = 0;
    this->scoreRender = new Text(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,TAILLE_SCORE, TAILLE_SCORE, {255, 255, 255, 255});
    std::string chaine = std::to_string(this->score);
    this->scoreRender->setText(chaine);


    try
    {
        map = new Map("assets/map/map1.txt", "assets/sprites/tilemap.png", renderer);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        currentState = Exit;
    }
}

/**
 * @brief Affiche le rendu du jeu complet
*/
void Game::renderGame()
{
    // Réinitialise l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    /* En fonction de l'état du jeu, affiche différente chose */
    switch (currentState)
    {
        /* Affiche le menu */
        case MainMenu:
            mainMenu->render(canContinue);
            break;
        /* Le jeu quand il est lancé */
        case Run:
        {
            /* Affiche la carte*/
            map->render(renderer);

            /* Affiche le joueur */
            this->player->render(renderer);
            
            /* Affiche le score */
            this->scoreRender->render();

            /* Affiche tous les equipements */
            equipements_t* currentEquipement = equipements; 
            while(currentEquipement != nullptr){
                Equipement* equipement = currentEquipement->val;
                equipement->render(renderer);
                currentEquipement = currentEquipement->next;
            }

            /* Affiche tous les ennemis */
            ennemies_t* currentEnemy = enemies;
            while (currentEnemy != nullptr)
            {
                Enemy* ennemi = currentEnemy->val;
                ennemi->render(renderer);
                currentEnemy = currentEnemy->next;
            }

            /* Affiche tous les projectiles */
            projectiles_t* currentProjectile = projectiles;
            while (currentProjectile != nullptr)
            {
                Projectile* projectile = currentProjectile->val;
                projectile->render(renderer);
                currentProjectile = currentProjectile->next;
            }

            /* Affiche la barre des PV */
            barHp->render(renderer);
            break;
        }
        /* Cas où le joueur meurt */
        case GameOver:
        {   
            /* Un nouveau texte pour dire que le joueur est mort, le rend à l'écran et sauvegarde son score */    
            g->setText("Game Over :((");
            g->render();
            break;
        }
        default:
            break;
    }

    // Render tout
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
        // Gère les événements du menu ; i.e les boutons
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
                        addEnemy(SCREEN_WIDTH / 3 + 200, SCREEN_HEIGHT / 2, WIDTH_ENNEMY, HEIGHT_ENNEMY);
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
                    case SDLK_ESCAPE:
                    {
                        if (currentState == Run or currentState == Settings or currentState == GameOver or currentState == Continue)
                        {
                            currentState = MainMenu;
                            this->saveGame();
                        }
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            /**
             * Permet d'arrêter de bouguer quand on relâche une touche
            */
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

/**
 * @brief Met à jour l'état de tout le jeu
*/
void Game::update()
{
    /* Commence le temps et tout le deltaTime tout ça */
    Uint32 currentTime, lastTime = SDL_GetTicks();
    double deltaTime = 0.f, elapsedTime = 0.f, elapsedTimeShootDelay = 0.f, timeSinceLastWave = 0.f;;
    float minDistance;

    /* S'active dès que le jeu se lance, se désactive quand on quitte la fenêtre */
    while (this->isRuning)
    {
        /* deltaTime basique, simple */
        currentTime = SDL_GetTicks();
        deltaTime = (double)(currentTime - lastTime) / 1000.0;
        lastTime = currentTime;        

        minDistance = SCREEN_WIDTH;

        elapsedTime += deltaTime;

        switch (currentState)
        {
            /* Met à jour le menu */
            case MainMenu:
                mainMenu->update(currentState);
                break;
            
            /* Commence une nouvelle partie */
            case NewGame:
                currentState = Run;
                newGame();
                break;

            /* En pleine partie */
            case Run:
            {
                this->canContinue = true;

                timeSinceLastWave += deltaTime;
                elapsedTimeShootDelay += deltaTime;

                if (timeSinceLastWave >= timeBetweenWaves) {
                    startNextWave();
                    timeSinceLastWave = 0.0;
                }

                /* Met à jour le joueur */
                this->player->update(deltaTime);

                /* Met à jour les ennemis et les potentiels collisions avec le joueur */
                ennemies_t* currentEnemy = enemies;
                bool isShooting = false;
                float angle = 0.f;
                while (currentEnemy != nullptr && currentEnemy->val != nullptr)
                {
                    
                    Enemy* ennemi = currentEnemy->val;
                    /* Si y a une collision (avec un délai de 0.5s), on perd de la vie et du score */
                    if (ennemi->collision(player) && elapsedTime >= .5f)
                    {
                        this->score = this->score - 2;
                        
                        player->setHP(player->getHP() - 10);
                        elapsedTime = 0.f;
                    }

                    /* Si le joueur doit tirer */
                    if (elapsedTimeShootDelay >= this->player->getShootDelay()) {
                        float currentDis = 0;
                        currentDis = ennemi->distance(player);
                        if (currentDis < minDistance)
                        {
                            minDistance = currentDis;
                            angle = atan2(ennemi->getY() - this->player->getY(), ennemi->getX() - this->player->getX()); 
                        }
                        isShooting = true;
                    }

                    /* Met à jour l'ennemi courant et son comportement et sa distance */
                    ennemi->behavior(player);
                    ennemi->update(deltaTime);

                    currentEnemy = currentEnemy->next;
                }
                if (isShooting)
                {
                    shoot(angle);
                    elapsedTimeShootDelay = 0.0;
                }
                

                // Réinitialise la boucle d'ennemis
                currentEnemy = enemies;

                /* Cette boucle met à jour les ennemis s'ils rencontrent un projectile */
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
                /***************************************************/

                /* Met à jour les projectiles */
                projectiles_t* currentProjectile = projectiles;
                while (currentProjectile != nullptr)
                {
                    Projectile* projectile = currentProjectile->val;
                    projectile->update(deltaTime);
                    if (projectile->getX() > SCREEN_WIDTH || projectile->getX() < 0  ||
                        projectile->getY() > SCREEN_HEIGHT || projectile->getY() < 0)
                    {
                        projectiles = remove(projectiles, projectile);
                        currentProjectile = projectiles;
                    }
                    else
                    {
                        currentProjectile = currentProjectile->next;
                    }                   
                }

                /* Met à jours les équipements et la collision avec le joueur*/
                equipements_t* currentstrucEquipement = equipements;
                while(currentstrucEquipement != nullptr){
                    bool equipementRemoved = false;
                    Equipement* currentEquipement = currentstrucEquipement->val;

                    /* En fonction du type d'équipement, change le joueur*/
                    if(player->collision(currentEquipement)){
                        
                        if(currentEquipement->getType() == 0){
                            player->setSpeed(player->getSpeed() + 20);
                        }
                        if(currentEquipement->getType() == 1){
                            player->setHP(player->getHP() + 5);
                        }
                        if(currentEquipement->getType() == 2){
                            this->score = this->score +10;                            
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

                /* Bouge la barre des PV si le joueur la touche */
                if(player->collision(barHp))
                {
                    barHp->moveBar();
                }

                barHp->setWidth(player->getHP());

                /* Met l'état à GameOver si le joueur n'a plus de PV */
                if (player->getHP() <= 0)
                {
                    currentState = GameOver;
                    canContinue = false;
                }


                std::string chaine = std::to_string(this->score);
                this->scoreRender->setText(chaine);
                
                break;
            }
            case GameOver:
                this->saveGame();
                this->saveBestScore();
                break;
            case Exit:
                this->isRuning = false;
                break;

            /* Si on continue, on lance une nouvelle partie (pour initialiser les variables) et on charge les données dans les variables */
            case Continue:
                newGame();
                loadGame();
                currentState = Run;
            default:
                break;
        }
        
        // Gère les événements et rend le jeu après tout ça 
        this->handleEvents();
        this->renderGame();                                             
    }    
   
}

/**
 * @brief Commence la prochaine vague et génère les ennemies
*/
void Game::startNextWave()
{
    waveNumber++;

    int numberOfEnemies = 3 + waveNumber * 2;

    for (int i = 0; i < numberOfEnemies; i++)
    {
        float x = rand() % SCREEN_WIDTH;
        float y = rand() % SCREEN_HEIGHT;
        addEnemy(x, y, WIDTH_ENNEMY, HEIGHT_ENNEMY);
    }
    
}

/**
 * @param x, y : La position initiale de l'ennemi
 * @param width, height : La largeur et hauteur de l'ennemi
 * 
 * @brief Ajoute un ennemi
*/
void Game::addEnemy(float x, float y, int width, int height)
{
    ennemies_t* nouvelEnnemi = new ennemies_t;
    nouvelEnnemi->val = new Enemy(HP_ENNEMY, SPEED_ENNEMY, x, y, width, height, renderer);
    nouvelEnnemi->next = enemies;
    enemies = nouvelEnnemi;
}

/**
 * @param typ : Le type de l'équipement (pour la modification du joueur / score)
 * @param couleur : La couleur de l'équipement
 * 
 * @brief Ajoute un équipement
*/
void Game::addEquipement(int typ, SDL_Color couleur)
{
    equipements_t* nouveauEquipement = new equipements_t;
    nouveauEquipement->val = new Equipement(typ,couleur);
    nouveauEquipement->next = equipements;
    equipements = nouveauEquipement;
}

/**
 * @param angle : L'angle de tir
 * 
 * @brief TIIIIIIIIIIIIRRE
*/
void Game::shoot(float angle)
{
    projectiles_t* proj = new projectiles_t;
    proj->val = new Projectile(player->getX() + player->getWidth() / 2, player->getY() + player->getHeight() / 2, angle, 100.f);
    proj->next = projectiles;
    projectiles = proj;    
}

/**
 * @brief Sauvegarde le meilleur score dans bestScore.dat.
*/
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

/**
 * @brief Sauvegarde l'état du jeu
*/
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

/**
 * @brief Charge l'état du jeu
*/
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
 * TODO: Version jouable
 * TODO: Fichier texte crash ???
 * TODO: Constantes
 * TODO: Valgrind (plus grand chose de leak à part des trucs sdl je crois)
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