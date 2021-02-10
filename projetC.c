#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#define BLEUCLAIR "\033[01;34m" // Pour définir des couleurs
#define ROUGE "\033[00;31m"
#define GREEN "\033[00;32m"
#define ORANGE "\033[00;33m"
#define BLEU "\033[00;34m"
#define SOULIGNE "\033[04m"
#define NORMAL "\033[00m"

int song[11];
int choosenNumber[11];

void displayGame(int level) { // Cette fonction permet de lancer le .txt en fonction du choix de l'utilisateur et d'afficher le jeux (level 1,level 2,level 3)
	FILE * fichier = NULL;
	int caractereActuel = 0;
    if (level == 1) {
	    fichier = fopen("./level/graphics-facile.txt", "r");
        if (fichier != NULL) {
            do 
			{
                caractereActuel = fgetc(fichier);
                printf("%c", caractereActuel);
            } while (caractereActuel != EOF);
            fclose(fichier);
        }
    } else if (level == 2) {
        fichier = fopen("./level/graphics-normal.txt", "r");
        if (fichier != NULL) {
            do {
                caractereActuel = fgetc(fichier);
                printf("%c", caractereActuel);
            } while (caractereActuel != EOF);
            fclose(fichier);
        }
    } else {
        fichier = fopen("./level/graphics-difficile.txt", "r");
        if (fichier != NULL) {
            do {
                caractereActuel = fgetc(fichier);
                printf("%c", caractereActuel);
            } while (caractereActuel != EOF);
            fclose(fichier);
        }
    }
}

void playRandomSong(int nbrCase, int randomSound, int song[]) { // Ici Cette fonction permet à l'ordinateur de choisir un nombre aléatoire entre 1 et 48 et permet de jouer les sons 
	char commandSong[128];
	int i;
	time_t t;
    srand((unsigned) time( & t)); // Nous avons ajouté cette fonction "srand(number)" car cela permet de changer la noyau aléatoire de la fonction rand(), 
    for (i = 1; i <= nbrCase; i++) { //si on avait utilisé juste la fonction rand() on aurai toujours la  même suite aléatoire.
        randomSound = rand() % 48;
        if (randomSound == 0) {
            randomSound = rand() % 48;
        }
        song[i] = randomSound; 
        snprintf(commandSong, sizeof(commandSong), "play -q ./songs/%d.mp3 &", randomSound); // ici la commande play sert à jouer le son aléatoire choisit par l'ordinateur variable (randomsound)
        system(commandSong);
        sleep(7);
    }
}

void putNumberPlayer(int puttingNumber, int nbrCase, int numberChoose, int choosenNumber[], char emoji[][10]) { //fonction qui met les emojis dans les cases en fonction du choix de l'utilisateur
	char confirm[4];											    //compris entre 1 et 48
	int cursorLocationY;
	do 
	{
	    int puttingNumber = 1;
	    for (puttingNumber = 1 ; puttingNumber <= nbrCase ; puttingNumber++)
        {
	        if (puttingNumber == 1) {
                cursorLocationY = 28;
                printf("\033[%d;%dH", 31, cursorLocationY);
                scanf("%d", & numberChoose);
                while (numberChoose < 0 || numberChoose > 48) {
                    printf("\033[%d;%dH", 31, cursorLocationY);
                    scanf("%d", & numberChoose);
                }
                printf("\033[%d;%dH", 33, cursorLocationY);
                if (numberChoose == 1) {
	        		choosenNumber[puttingNumber] = numberChoose;
	        	    printf("%s", "🐸");
	            } else {
	        		choosenNumber[puttingNumber] = numberChoose;
	        		printf("%s", emoji[numberChoose - 1]);
	        	}
             } else {
                cursorLocationY = cursorLocationY + 10;
                printf("\033[%d;%dH", 31, cursorLocationY);
                scanf("%d", & numberChoose);
                while (numberChoose < 0 || numberChoose > 48) {
                    printf("\033[%d;%dH", 31, cursorLocationY);
                    scanf("%d", & numberChoose);
                }
                printf("\033[%d;%dH", 33, cursorLocationY);
                if (numberChoose == 1) {
	        		choosenNumber[puttingNumber] = numberChoose;
	        	    printf("%s", "🐸");
	            } else {
	        		choosenNumber[puttingNumber] = numberChoose;
	        		printf("%s", emoji[numberChoose - 1]);
	        	}
            }
        }
	    printf("\033[%d;%dH",37,6);
	    printf("                                                                                   "); 
	    printf("\033[%d;%dH",37,6);
	    printf("Confirmez-vous vos choix oui/non ? : ");
        scanf("%s", confirm);
    }while(strcmp(confirm,"non")==0);
	printf("\033[%d;%dH",37,6);
	printf("                                                                                   ");
}

void resultGame(int puttingResult, int nbrCase, int choosenNumber[], int song[]) { //Cette fonction permet à l'ordinateur de comparer la réponse de l'utilisateur avec le choix aléatoire de l'ordi
    int cursorLocationY = 28;
    for (puttingResult = 1 ; puttingResult <= nbrCase ; puttingResult++)
    {
    	if (song[puttingResult] == choosenNumber[puttingResult]) {
    		printf("\033[%d;%dH", 35, cursorLocationY);
    		printf("✅");
    		cursorLocationY = cursorLocationY + 10;
    	} else {
    		printf("\033[%d;%dH", 35, cursorLocationY);
    		printf("❌");
    		cursorLocationY = cursorLocationY + 10;
    	}
    }
}

int main() {
    system("clear");
    char emoji[48][10] = {"🐸", "🐤", "🐎", "🐍", "🐪", "🐘", "🐷", "🐐", "🐶", "🐔", "🦆", "🙉", "🧯", "📸", "☎️", "📺", "📻", "🔨", "⌚", "🚽", "🚿", "🎥", "📱","💿", "⚽", "🏀", "🎱", "🏓", "🏹", "⛳", "🥊", "⛸️", "🏋️ ", "🏊", "🏇", "🎳", "🚙", "🚲", "🚔", "🚑", "🏍️", "🛹", "🚌", "🚊", "🚁", "✈️ ", "🚀", "🚢"};
    char replay[5];
    int playIntro = 0;
    do 
	{
	system("clear");
    int level;
    int nbrCase;
    int randomSound;
    int numberChoose;
    int puttingNumber = 1;
    int puttingResult = 1;
	time_t t;
    printf(SOULIGNE "BIENVENUE SUR LE JEU MEMORY SONORE :\n\n"NORMAL);//Affichage des niveaux
    printf(GREEN "(1) -> Niveau Facile\n"NORMAL);
    printf(ORANGE "(2) -> Niveau Normal\n"NORMAL);
    printf(ROUGE "(3) -> Niveau Difficile\n"NORMAL);
    printf("\n\nVeuillez choisir un niveau de difficulté : ");
    srand((unsigned) time( & t));
	if (playIntro == 0) {
        system("play -q ./songs/intro.mp3 &");//Permet de lancer le son de l'intro la première fois que le joueur lance le jeux.
        sleep(42);
	    playIntro = playIntro + 1;
	}
    scanf("%d", & level);
    system("clear");
    switch (level) { //En fonction des niveaux que l'on choisit, on obtient ("3 sons aléatoires pour le niveau 1, 5 pour le 2, et enfin 10 pour le 3)
        case 1:
            system("clear");
            nbrCase = 3;
            displayGame(level);
            playRandomSong(nbrCase, randomSound, song);
            putNumberPlayer(puttingNumber, nbrCase, numberChoose, choosenNumber, emoji);
            resultGame(puttingResult, nbrCase, choosenNumber, song);
            break;
        case 2:
            system("clear");
            nbrCase = 5;
		    displayGame(level);
            playRandomSong(nbrCase, randomSound, song);
            putNumberPlayer(puttingNumber, nbrCase, numberChoose, choosenNumber, emoji);
            resultGame(puttingResult, nbrCase, choosenNumber, song);
            break;
        case 3:
            system("clear");
            nbrCase = 10;
            displayGame(level);
            playRandomSong(nbrCase, randomSound, song);
            putNumberPlayer(puttingNumber, nbrCase, numberChoose, choosenNumber, emoji);
            resultGame(puttingResult, nbrCase, choosenNumber, song);
            break;
    }
    printf("\033[%d;%dH",37,6);
    printf("Voulez-vous rejouer oui/non ? : ");
    scanf("%s", replay);
    }while(strcmp(replay,"oui")==0);
    system("clear");
    printf("Merci d'avoir joué à notre jeu, à bientôt ! \n ");
    sleep(30);      
	return 0;
}
