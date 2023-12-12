#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define TITLE "Jeu de dingue"

/* Constante du menu */
#define NB_BOUTON_MENU 3

/*Constante de score*/
#define TAILLE_SCORE 20

/* Constante de player */
//hp
#define HP_PLAYER 100
//speed
#define SPEED_PLAYER 160.0f
//taille 
#define WIDTH_PLAYER 64
#define HEIGHT_PLAYER 64
/**********************/

/* Constante de la bar des PV */
//taille
#define WIDTH_BAR_HP 100
#define HEIGHT_Y_BAR_HP 30
//coord
#define CORD_X_BAR_HP 10
#define CORD_Y_BAR_HP 10
//couleur
#define COUL_BAR_HP {255, 0, 0, 0}
// Couleur par défaut de la barre
#define BAR_DEFAULT_COLOR {255, 0, 0, 0}
//ajout de hp au debug
#define AJOUT_HP 10
//changement de coteer de la bar d'hp
#define CHGT_COTE 10
/****************************/

/* Constante du texte de game over */
/*********************************/

/* Constante des équipements */
//couleur par defaut 
#define COUL_PAR_DEF {0,0,255,0}
/******************************/

/* Constante des ennemies */
//taille par defaut des ennemy
#define WIDTH_ENNEMY 30
#define HEIGHT_ENNEMY 30
//caractéristique de tous les nenemy
#define HP_ENNEMY 20
#define SPEED_ENNEMY 40.0f
//taille pour les animations des ennemies (taille de l'image)
#define HEIGHT_ANIM_ENNEMY 640
#define WIDTH_ANIM_ENNEMY 640
/***************************/

/* Constant du menu */
//Couleur du titre dans le menu
#define COUL_TEXT {255, 0, 255, 255}
#define COUL_BOUT_DEFAULT {0, 120, 255, 255}

/*************************/
#endif