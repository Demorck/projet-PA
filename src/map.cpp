#include <stdlib.h>
#include <stdio.h>
#include <map.hpp>

char** allouer_tab_2D(int n, int m){
    char** T2C =(char**)malloc(n*sizeof(char*));
        if(T2C == NULL){
            return NULL;
        }
    for (int i = 0;i<n;i++){
        T2C[i] = (char*)malloc(m*sizeof(char));
    }
    for(int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            T2C[i][j]=' ';
        }
    }
    return T2C;
}

void desallouer_tab_2D(char** tab, int n){
    for (int i = 0; i<n; i++){
        free(tab[i]);
    }
    free(tab);
}

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
	FILE* file = fopen(nomFichier, "r");
    if (file == NULL) {
        printf("Impossible d’ouvrir le fichier.\n");
        return;
    }

    *nbLig = 0;
    *nbCol = 0;
    int current_col = 0;
    int max_col = 0;

    int c;
	while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            (*nbLig)++;
            max_col = (current_col > max_col) ? current_col : max_col;
            current_col = 0;
        } else {
            current_col++;
        }
    }
	if (current_col > 0) {
        (*nbLig)++;
        max_col = (current_col > max_col) ? current_col : max_col;
    }

    *nbCol = max_col;

    fclose(file);
}

char** lire_fichier(const char* nomFichier){
	 FILE* file = fopen(nomFichier, "r");
    if (file == NULL) {
        printf("Impossible d’ouvrir le fichier.\n");
        return NULL;
    }

    int nbLig, nbCol;
    taille_fichier(nomFichier, &nbLig, &nbCol);

    char** tab = allouer_tab_2D(nbLig, nbCol);

    if (tab == NULL) {
        fclose(file);
        return NULL;
    }

    int lig = 0;
    int col = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lig++;
            col = 0;
        } else {
            
            tab[lig][col] = (char)c;
            col++;
        }
    }
	
    fclose(file);
	tab[lig] = NULL;
    return tab;
}
/*fonction qui affiche des sprite avec un tab de char en 2D*/
void afficher(char** tab,const char* nomFichier){
    int nbl=0;
    int nbc=0;
    taille_fichier(nomFichier, &nbl,&nbc);
    for(int i = 0; i<nbl; i++){
        for(int j = 0; j<nbc; j++){
            switch (tab[i][j]) {
                case 1:
           
                break;
                case 2:
           
                break;
                case 3:
            
                break;
                default:
                /*aller chercher les sprites*/
                break;
    }
        }
    }
}//a completer 
