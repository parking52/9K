#ifndef _LEONIDAS_H
#define _LEONIDAS_H

#include "Map.h"

/**
 *	\struct Leonidas
 *	\brief structure contenant les informations sur le personnage que contrôle le joueur
 */
struct sLeonidas 
{
        int x;
        int y;
        int hp;
};typedef struct sLeonidas Leonidas;

/**
 *	\fn void leoInit(Leonidas * leo)
 *	\brief Initialise la structure Leonidas 
 */
void leoInit(Leonidas * leo);

/**
 *	\fn void leoGauche(Leonidas * leo, const map * Map)
 *	\brief Fais bouger le personnage sur la case de gauche si la position est valide
 */
void leoGauche(Leonidas * leo, const map * Map);

/**
 *	\fn void leoDroite(Leonidas * leo, const map * Map)
 *	\brief Fais bouger le personnage sur la case de droite si la position est valide
 */
void leoDroite(Leonidas * leo, const map * Map);

/**
 *	\fn void leoHaut(Leonidas * leo, const map * Map)
 *	\brief Fais bouger le personnage sur la case du dessus si la position est valide
 */
void leoHaut(Leonidas * leo, const map * Map);

/**
 *	\fn void leoBas(Leonidas * leo, const map * Map)
 *	\brief Fais bouger le personnage sur la case du dessous si la position est valide
 */
void leoBas(Leonidas * leo, const map * Map);

/**
 *	\fn int leoGetX(const Leonidas * leo)
 *	\brief Renvoie le champ x de la structure Leonidas
 */
int leoGetX(const Leonidas * leo);

/**
 *	\fn int leoGetY(const Leonidas * leo)
 *	\brief Renvoie le champ y de la structure Leonidas
 */
int leoGetY(const Leonidas * leo);




#endif
