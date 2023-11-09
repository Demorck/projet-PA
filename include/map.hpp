#include <stdlib.h>
#include <stdio.h>

char** allouer_tab_2D(int n, int m);

void desallouer_tab_2D(char** tab, int n);

void afficher(char** tab);//a completer 

void taille_fichier(const char* nomfichier, int*nbLig, int* nbCol);

char** lire_fichier(const char* nomfichier);