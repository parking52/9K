
#ifndef _SDLJEU_H
#define _SDLJEU_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Jeu.h"

/**
 *	\struct sdlJeu
 *	\brief Structure contenant tout les champs SDL_Surface, la police utilisée (TTF_Font) ainsi qu'un champ mode et finalscore
 */
struct ssdljeu
{
        Jeu j;
	
	/*	IMAGE	*/
        SDL_Surface * surface_ecran;
        SDL_Surface * surface_9K;
        SDL_Surface * surface_sable;
	SDL_Surface * surface_javelot;
	SDL_Surface * surface_imgd;
	SDL_Surface * surface_imgv;
	SDL_Surface * surface_imgmenu;
	
	/*	TEXTE	*/
	SDL_Surface * surface_score_hp;
	SDL_Surface * surface_nbScore;
	SDL_Surface * surface_nbHp;
	SDL_Surface * surface_ill_texte;
	SDL_Surface * surface_finalscore;
	
	TTF_Font * police;
	
	int mode;
	int finalscore;
	
};typedef struct ssdljeu sdlJeu;

/**
 *	\fn void sdljeuInit(sdlJeu * sjeu)
 *	\brief Initialise la structure sdlJeu
 *	Ouvre et initialise la police avec TTF_Init et TTF_OpenFont
 *	Ouvre et initialise la SDL, mise en place de l'ecran principal (taille)
 *	Initialise le Jeu, la Map et charge les différentes SDL_Surface qui apparaissent sur le terrain de jeu (javelot, leonidas, sable)
 */
void sdljeuInit(sdlJeu * sjeu);

/**
 *	\fn void sdljeuDetruit(sdlJeu * sjeu)
 *	\brief Libere les champs surface_9K, surface_sable, surface_javelot
 *	Ferme le module SDL_ttf, TTF_CloseFont puis TTF_Quit
 *	Ferme le module SDL : SDL_Quit
 */
void sdljeuDetruit(sdlJeu * sjeu);

/**
 *	\fn void sdljeuAff(sdlJeu * sjeu)
 *	\brief Fonction qui gere l'affichage du score, des hps, des SDL_surface de la map, du joueur et des ennemis sur l'écran
 */
void sdljeuAff(sdlJeu * sjeu);

/**
 *	\fn void sdljeuBoucle(sdlJeu * sjeu)
 *	\brief Fonction qui gère le déroulement du jeu en SDL
 *	Elle contient les menus du jeu ainsi que les deux modes de difficulté du jeu
 * 	On y retrouve une utilisation de FMOD pour jouer des sons et de la musique 
 * 	Cette boucle présente un appel récursif d'elle même tant qu'on souhaite jouer
 */
void sdljeuBoucle(sdlJeu * sjeu);

/**
 *	\fn  SDL_Surface *SDL_load_image(const char* filename)
 *	\brief Fonction qui renvoie le chargement d'une image dans un type SDL_Surface *
 */
SDL_Surface *SDL_load_image(const char* filename);

/**
 *	\fn void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y )
 *	\brief Fonction qui applique un type SDL_Surface * sur un autre en coordonnée x,y de la destination
 */
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y );

#endif
