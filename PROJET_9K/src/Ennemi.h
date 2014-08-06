#ifndef _ENNEMI_H
#define _ENNEMI_H

#include "Map.h"
#include "Leonidas.h"

/**
 *	\struct Ennemi
 *	\brief structure contenant les informations sur un ennemi
 */
struct sEnnemi
{
        int x;
        int y;
        int age;
};typedef struct sEnnemi Ennemi;

/**
 *	\struct Tableau_ennemi
 *	\brief structure contenant un tableau dynamique d'ennemi, sa taille et le score
 */
struct tEnnemi
{
        int taille;
        int score;
        Ennemi **Tenn;
};typedef struct tEnnemi Tableau_ennemi;

/**
 *	\fn  void ennInit(Ennemi *enn)
 *	\brief Initialise la structure Ennemi
 */
void ennInit(Ennemi *enn);

/**
 *	\fn void ennBas(Ennemi *enn, const map * Map)
 *	\brief Fais bouger un ennemi sur la case du dessous
 */
void ennBas(Ennemi *enn, const map * Map);

/**
 *	\fn void tabennInit(Tableau_ennemi *Te, int a)
 *	\brief Initialise la structure Tableau_ennemi et alloue la mémoire réquise pour le le tableau d'ennemi qu'elle contient
 */
void tabennInit(Tableau_ennemi *Te, int a);

/**
 *	\fn void ennTour(Tableau_ennemi *Te, const map *Map, Leonidas *leo)
 *	\brief Fait déscendre tout les ennemis du tableau d'ennemi d'une case vers le bas
 *      Appel aux fonctions ennBas, incrementeAge et collision_enn
 */
void ennTour(Tableau_ennemi *Te, const map *Map, Leonidas *leo);

/**
 *	\fn void libereEnnemi(Tableau_ennemi *Te, int i)
 *	\brief Libère la mémoire allouée pour l'ennemi de la case i du tableau d'ennemi
 */
void libereEnnemi(Tableau_ennemi *Te, int i);

/**
 *	\fn void libererToutEnnemi(Tableau_ennemi *Te)
 *	\brief Libère la totalité du tableau d'ennemi
 */
void libererToutEnnemi(Tableau_ennemi *Te);

/**
 *	\fn int ennGetY(const Ennemi *enn)
 *	\brief Renvoie la coordonnée x d'un ennemi
 */
int ennGetY(const Ennemi *enn);

/**
 *	\fn int ennGetX(const Ennemi *enn)
 *	\brief Renvoie la coordonnée y d'un ennemi
 */
int ennGetX(const Ennemi *enn);

/**
 *	\fn void ajouteEnnemi(Tableau_ennemi *Te)
 *	\brief Alloue la mémoire pour un ennemi puis appel ennInit pour l'initialiser et ajouteEnnemiDansTableau pour l'insérer dans le tableu d'ennemi 
 */
void ajouteEnnemi(Tableau_ennemi *Te);

/**
 *	\fn void ajouteEnnemiDansTableau(Tableau_ennemi *Te,Ennemi *enn)
 *	\brief Parcours le tableau d'ennemi jusqu'à la premiere case NULL et la remplit avec l'ennemi enn
 */
void ajouteEnnemiDansTableau(Tableau_ennemi *Te,Ennemi *enn);

/**
 *	\fn void newWave(Tableau_ennemi *Te)
 *	\brief On appel 5 fois ajouteEnnemi pour créer des vagues de 5 ennemis
 */
void newWave(Tableau_ennemi *Te);

/**
 *	\fn void incrementeAge(Ennemi *enn)
 *	\brief Augmente l'age d'un ennemi de 1 à chaque fois que incrementeAge est appelé pour un ennemi enn
 */
void incrementeAge(Ennemi *enn);

/**
 *	\fn void testAge(Tableau_ennemi *Te)
 *	\brief Test l'age de tout les ennemis du tableau d'ennemi
 *	Si l'age d'un ennemi est égal à 15 on augmente le score de 20 
 *	(l'ennemi est arrivé au bout et à été correctement évité par le joueur) et on le libère par un appel de libereEnnemi
 */
void testAge(Tableau_ennemi *Te);

/**
 *	\fn void collision_enn(Tableau_ennemi *Te, int i, Leonidas *leo)
 *	\brief Test si l'ennemi contenu à la case i du tableau d'ennemi descend sur une case occupé par le joueur, si c'est le cas la case i du tableau d'ennemi contenant l'ennemi 
 *	en question est libèré et le joueur perd un point de vie
 */
void collision_enn(Tableau_ennemi *Te, int i, Leonidas *leo);

/**
 *	\fn void collision_leo(Tableau_ennemi *Te, Leonidas *leo)
 *	\brief Parcours tout le tableau d'ennemi (de 0 à 224, incrément i) et test si la case sur laquelle le joueur se déplace est occupé par un ennemi ou non, si c'est le cas la case i du tableau d'ennemi 
 *	est libèrée et le joueur perd un point de vie
 */
void collision_leo(Tableau_ennemi *Te, Leonidas *leo);

#endif