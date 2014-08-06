
#ifndef _JEU_H
#define _JEU_H

#include "Leonidas.h"
#include "Map.h"
#include "Ennemi.h"
#include <sys/time.h>

/**
 *	\struct Jeu
 *	\brief structure contenant les informations sur le jeu, c'est à dire la map le joueur le tableau d'ennemi et les informations sur le temps
 */
struct sJeu
{
        map map;
        Leonidas leo;
        Tableau_ennemi TabE;
	struct timeval temps_precedent;
	int intervalle;
};typedef struct sJeu Jeu;

/**
 *	\fn void jeuInit(Jeu * j)
 *	\brief Initialise la structure Jeu
 */
void jeuInit(Jeu * j);

/**
 *	\fn map *jeuGetMapPtr(Jeu * j)
 *	\brief Renvoie le poiteur sur map du champ map de la structure Jeu
 */
map *jeuGetMapPtr(Jeu * j);

/**
 *	\fn Leonidas *jeuGetLeonidasPtr(Jeu * j)
 *	\brief Renvoie le pointeur sur joueur du champ leo de la structure Jeu
 */
Leonidas *jeuGetLeonidasPtr(Jeu * j);

/**
 *	\fn Ennemi *jeuGetEnnemiPtr(Jeu *j, int a)
 *	\brief Renvoie le poiteur sur l'ennemi a du Tableau_ennemi TabE de la structure Jeu
 */
Ennemi *jeuGetEnnemiPtr(Jeu *j, int a);

/**
 *	\fn int JeuGetNbEnn(const Jeu *j)
 *	\brief Renvoie le nombre d'ennemi contenu dans le Tableau_ennemi TabE de la structure Jeu
 */
int JeuGetNbEnn(const Jeu *j);

/**
 *	\fn const Ennemi *jeuGetConstEnnemiPtr(const Jeu *j, int a)
 *	\brief Renvoie l'ennemi numero a peut importe sa place dans le Tableau_ennemi TabE
 */
const Ennemi *jeuGetConstEnnemiPtr(const Jeu *j, int a);

/**
 *	\fn const map *jeuGetConstMapPtr(const Jeu * j)
 *	\brief Renvoie le poiteur sur map du champ map de la structure Jeu
 */
const map *jeuGetConstMapPtr(const Jeu * j);

/**
 *	\fn void mapInit(map * Map)
 *	\brief Renvoie le pointeur sur joueur du champ leo de la structure Jeu
 */
const Leonidas *jeuGetConstLeonidasPtr(const Jeu * j);

/**
 *	\fn void jeuActionClavier(Jeu *j, const char)
 *	\brief Fonction de déplacement du joueur avec les flèches directionnelles, un appel à collision_leo est fait a chaque déplacement
 */
void jeuActionClavier(Jeu *j, const char);

/**
 *	\fn int temps_jeu(Jeu *j)
 *	\brief Fonction cruciale du mode classique du jeu, elle fait apparaitre et descendre les ennemis par un appel de newWave et de ennTour selon un intervalle
 */
int temps_jeu(Jeu *j);

/**
 *	\fn int temps_jeu_illimite(Jeu *j)
 *	\brief Fonction cruciale du mode illimité du jeu, elle fait apparaitre et descendre les ennemis par un appel de newWave et de ennTour selon un intervalle
 */
int temps_jeu_illimite(Jeu *j);

#endif
