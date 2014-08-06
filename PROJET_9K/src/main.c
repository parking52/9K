#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "ncursJeu.h"
#include "sdlJeu.h"

int main ( int argc, char** argv )
{
        srand( (unsigned)time(NULL) );/* définition "aléatoire", basé sur la fonction time, des seeds pour les fonctions rand du programme */
	
	#ifdef JEU_SDL /* Si le makefile est "paramètré" pour lancer le jeu en SDL */
	sdlJeu sj;
	sdljeuBoucle(&sj) ;
	sdljeuDetruit(&sj);
	#endif
	
	#ifdef JEU_NCURSES /* Sil le makefil est paramètré pour lancer le jeu en ncurses */
	Jeu jeu;
	jeuInit(&jeu);
	getch();
	ncursBoucle(&jeu);
	#endif
        return 0;
}
