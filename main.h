#include <stdlib.h>

typedef struct Joueurs Joueurs;
struct Joueurs{

    char nom[100];
    int score;
};

char lireCaractrere();
void initialiser(char affichée[],char devineMoi[]);
void afficher(char affichée[],char devineMoi[], char caractere,int *scoreAdress);
void aDeviner(char devineMoi[],FILE* fichier);
void theme(FILE** fichier);
void scoreListe(int score, char nom[]);