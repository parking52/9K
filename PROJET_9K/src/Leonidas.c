#include "Leonidas.h"
#include "Ennemi.h"
#include "stdlib.h"


void leoInit(Leonidas * leo)
{
        leo->x=7;
        leo->y=14;
        leo->hp=5;
}	

void leoGauche(Leonidas *leo, const map *Map)
{
        if (mapEstPositionPersoValide(Map, leo->x-1, leo->y))
        {
                leo->x--;
        }
}

void leoDroite(Leonidas *leo, const map *Map)
{
        if (mapEstPositionPersoValide(Map, leo->x+1, leo->y))
        {
                leo->x++;
        }
}

void leoHaut(Leonidas *leo, const map *Map)
{
        if (mapEstPositionPersoValide(Map, leo->x, leo->y-1))
        {
                leo->y--;
        }
}

void leoBas(Leonidas *leo, const map *Map)
{
        if (mapEstPositionPersoValide(Map, leo->x, leo->y+1))
        {
                leo->y++;
        }
}

int leoGetX(const Leonidas *leo)
{
        return leo->x;
}

int leoGetY(const Leonidas *leo)
{
        return leo->y;
}
