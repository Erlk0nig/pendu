#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "main.h"
int main() {
    char rejouer=0;
    srand(time(NULL));

    // Repeter le jeu jusqu'a rejouer == n    
    while(rejouer != 'n'){
        FILE* fichier = NULL;
        int score = 1000;
        int *scoreAdress = &score;
        // initialisation de la chaine ou on va mettre le mot a deviner
        char devineMoi[100]="";
        char *affichée=NULL;
        affichée = malloc(strlen(devineMoi) * sizeof(char));
        char caractere=0;
        char nom[100]="";
    theme(&fichier);
    aDeviner(devineMoi,fichier);
    initialiser(affichée,devineMoi);
    do{
    printf("A Deviner : %s\n",affichée);
    printf("Devine !! : ");
    caractere = lireCaractrere();
    afficher(affichée,devineMoi,caractere,scoreAdress);
    printf("Score : %d\n",score);

    // Condition d'arret si le joueur gagne 
    if (strcmp(devineMoi,affichée) == 0){
        printf("Félicitations vous avez gagner !!!\n");
        break;
    }
    // Condition d'arret si le joueur perd
    if(score <=0){
        printf("Vous avez perdu :(\n");
        printf("%s\n",devineMoi);
        break;
    }

    }while(1);

    printf("Veuiller saisir votre nom : ");
    scanf("%100s",nom);
    // Afiichage du score
    scoreListe(score,nom);
    printf("rejouer (y/n) : ");
    //Lire rejouer
    rejouer = getchar();
    free(affichée);
    
    }

    return 0;
}

// Initiailisation de '******'
void initialiser(char affichée[],char devineMoi[]) {

    for (int i = 0; i < strlen(devineMoi); i++)
    {
        affichée[i] = '*';
    }
}

// Lecture de caractére pour deviner
char lireCaractrere() {
    char caractere=0;
    caractere = getchar();
    // enlever \n de caractere
    if (caractere == '\n')
        caractere = getchar();

    // passage au majuscule
    caractere = toupper(caractere);
    // Lecture jusqu'a la fin de ligne
    while(getchar() != '\n');

    return caractere;
}
// Affichage de la lettre devinée 
void afficher(char affichée[],char devineMoi[], char caractere,int *scoreAdress){
    // Initialisation de vrai
    int vrai = 0;
    for(int i=0; i<strlen(devineMoi); i++){
        if(caractere == devineMoi[i]){
            affichée[i] = caractere;
            // Modifier vrai si le caractere existe
            vrai = 1;

        }
    }
    if (vrai == 0)
        // Si vrai reste 0 le score diminue
        *scoreAdress -= 100;    
}

void aDeviner(char devineMoi[], FILE* fichier) {

    int min=0,max=0;

    if(fichier != NULL){
        // Début du ficher
        fseek(fichier,1,SEEK_SET);
        min = ftell(fichier);

        // Fin du fichier
        fseek(fichier,-1,SEEK_END);
        max = ftell(fichier);

        while (1)
        {
            // Nombre aléatoire
            int random_number = min + rand() % (max - min +1 );

            // Mettre le curseur en une place aléatoire 
            fseek(fichier,random_number,SEEK_SET);

            // Lire la chaine si le curseur est placé au début de la ligne
            if (getc(fichier) == '\n'){

                if (fscanf(fichier,"%s",devineMoi) == 1){
                    for(int i=0 ;i< strlen(devineMoi);i++){
                        devineMoi[i] = (char)toupper((int)devineMoi[i]);
                    }

                }
                break;
            }
        }        
        fclose(fichier);
    }
}
// Selection de fichier des mots a deviner
void theme(FILE** fichier){

    int theme=0;
    // chaine de caractere choix
    char *choix=NULL;
    // Menu
    do {
        printf("\t\t\t####PENDU####");
        printf("\n");
        printf("Théme: \n");
        printf("1-Animaux\n");
        printf("2-Couleurs\n");
        printf("3-Fruits\n");
        printf("4-Metiers\n");
        printf("5-Pays\n");
        printf("6-Sports\n");
        printf("7-Vetements\n");
        printf("8-Voiture\n");
        printf("9-Aleatoire\n");
        printf("SELECT : ");
        scanf("%d",&theme);
    }while(theme < 1 || theme > 9);

    // Selection de fichier aléatoire
    if(theme == 9){
        srand(time(NULL));
        theme = 1 + rand()% 8;
    }

    // Selection de choix
    switch (theme)
    {
    case 1 :
        choix = "animaux.txt";
    
        break;

    case 2 :
        choix = "couleurs.txt";
    
        break;
    case 3 :
        choix = "fruits.txt";
    
        break;

    case 4 :
        choix = "metiers.txt";
    
        break;
    
    case 5 :
        choix = "pays.txt";
    
        break;

    case 6 :
        choix = "sports.txt";
    
        break;
    
    case 7 :
        choix = "vetements.txt";
    
        break;
    
    case 8 :
        choix = "voitures.txt";
    
        break;
    
    }

    // Ouverture de fichier
    *fichier = fopen(choix,"r");

}

void scoreListe(int score, char nom[]){
    FILE* fichier = NULL;
    char caractere = 0;
    int nombreDeLignes = 0;
    int nombreCaractere =0;
    int j=0;
    char *chainefichier=NULL;
   
    // Struct tableau de joueurs
    Joueurs joueurs[10] = {"",0};

    fichier = fopen("scores.txt","r");

    // Calcul de nombre de lignes
    if(fichier != NULL){

        while((caractere = getc(fichier)) != EOF ){
            nombreCaractere++;
            if (caractere == '\n')
                nombreDeLignes++;
        }
        

        rewind(fichier);

     
        // Ecriture du nom et du score    
        fprintf(fichier,"%s,%d\n",nom,score);

        // Allocation de memoire pour chainefichier     
        rewind(fichier);
        chainefichier = (char *)malloc(sizeof(char) * nombreCaractere +1);

      while(fgets(chainefichier,nombreCaractere,fichier) != NULL){

        chainefichier[nombreCaractere-1] = '\0';
    
        // Separation de nom et score
        char *token = strtok(chainefichier,",");
        // Liste de noms
        if(token != NULL){
            strncpy(joueurs[j].nom,token,sizeof(joueurs[j].nom)-1);
            joueurs[j].nom[sizeof(joueurs[j].nom)-1] = '\0';
            
        }

        // Liste de joueurs
        token = strtok(NULL,",");
        if (token != NULL){
            joueurs[j].score = atoi(token);
        }
        j++;
      }
    
        // Tri des noms et des scores
      for(int i=0;i<nombreDeLignes;i++){
        for(int j=i+1;j<nombreDeLignes+1;j++){
            if(joueurs[i].score < joueurs[j].score){
                char boxnom[100]="";
                int boxscore=0;

                boxscore = joueurs[i].score;
                
                strncpy(boxnom,joueurs[i].nom,sizeof(boxnom)-1);
                boxnom[sizeof(boxnom) - 1]= '\0';
                
                joueurs[i].score = joueurs[j].score;
                
                strncpy(joueurs[i].nom,joueurs[j].nom,sizeof(joueurs[j].nom)-1);
                joueurs[j].nom[sizeof(joueurs[j].nom)-1] = '\0';
                
                joueurs[j].score = boxscore;
                
                strncpy(joueurs[j].nom,boxnom,sizeof(boxnom)-1);
                boxnom[sizeof(boxnom) - 1]= '\0';

            }
        }
        
      }

        // Affichage des scores
      for(int i=0;i<10;i++){
        printf("%d- %s : %d\n",i+1,joueurs[i].nom,joueurs[i].score);
      }
    }   
        free(chainefichier);
        fclose(fichier);
    
   
    // Le joueur doit saisir entrer
    printf("Saisir ENTRER pour continuer");
    getchar();
    getchar();
}   