#ifndef _MAP_H
#define _MAP_H


/**
 *	\struct map
 *	\brief structure contenant les informations sur la map, le score et un tableau de caractères
 */
struct smap
{
        int dimx;
        int dimy;
        int score;
        char **tab;
};typedef struct smap map;

/**
 *	\fn void mapInit(map * Map)
 *	\brief Initialise la structure map et alloue en mémoire la place qu'il nous faut pour l'utiliser
 */
void mapInit(map * Map);

/**
 *	\fn void mapLibere(map * Map)
 *	\brief Libère la mémoire alloué par mapInit et remet à NULL / 0 les champs de la structure map
 */
void mapLibere(map * Map);

/**
 *	\fn int mapEstPositionPersoValide(const map * Map, const int x, const int y)
 *	\brief Test qui renvoie 1 si la position du personnage est valide, 0 sinon
 */
int mapEstPositionPersoValide(const map * Map, const int x, const int y);

/**
 *	\fn int mapEstPositionEnnemiValide(const map * Map, const int x, const int y)
 *	\brief Test qui renvoie 1 si la position de l'ennemi est valide, 0 sinon
 */
int mapEstPositionEnnemiValide(const map * Map, const int x, const int y);

/**
 *	\fn const char mapGetXY(const map * Map, const int x, const int y)
 *	\brief Récupère la case x,y du tableau de char de la structure map
 */
const char mapGetXY(const map * Map, const int x, const int y);

/**
 *	\fn void mapSetXY(const map * Map, const int x, const int y, const char item)
 *	\brief Remplit la case x,y du tableau de char de la structure map
 */
void mapSetXY(const map * Map, const int x, const int y, const char item);

/**
 *	\fn const int mapDimX(const map * Map)
 *	\brief Renvoie le champ dimx de la structure map
 */
const int mapDimX(const map * Map);

/**
 *	\fn const int mapDimY(const map * Map)
 *	\brief Renvoie le champ dimy de la structure map
 */
const int mapDimY(const map * Map);

#endif
