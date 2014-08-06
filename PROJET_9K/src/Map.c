#include "Map.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

void mapInit(map *Map)
{
        int x,y;
        const char map_defaut[29][29] = {
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "...............",
                "..............." };

                Map->dimx = 29;
                Map->dimy = 29;
	
                Map->tab = (char **)malloc(Map->dimy*sizeof(char *));
                for (y=0; y<Map->dimy; y++)
                {
                        Map->tab[y] = (char *)malloc(Map->dimx*sizeof(char));
                }
                for(y=0;y<Map->dimy;++y)
                {
                        for(x=0;x<Map->dimx;++x)
                        {
                                Map->tab[y][x] = map_defaut[y][x];
                        }
                }
}

void mapLibere(map *Map)
{
        int y;
        for (y=0; y<Map->dimy; y++)
        {
                free(Map->tab[y]);
                free(Map->tab);
        }
        Map->dimx = 0;
        Map->dimy = 0;
        Map->tab = NULL;
}

int mapEstPositionPersoValide(const map *Map, const int x, const int y)
{
        if (x>=0 && x<Map->dimx-14 && y>=0 && y<Map->dimy-14 && Map->tab[y][x]!='#')
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

int mapEstPositionEnnemiValide(const map *Map, const int x, const int y)
{
        if (x>=0 && x<Map->dimx-15 && y>=0 && y<Map->dimy)
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

const char mapGetXY(const map *Map, const int x, const int y)
{
        assert(x>=0);
        assert(y>=0);
        assert(x<Map->dimx);
        assert(y<Map->dimy);
        return Map->tab[y][x];
}

void mapSetXY(const map *Map, const int x, const int y, const char item)
{
        assert(x>=0);
        assert(y>=0);
        assert(x<Map->dimx);
        assert(y<Map->dimy);
        Map->tab[y][x] = item;
}

const int mapDimX(const map *Map)
{
        return Map->dimx;
}

const int mapDimY(const map *Map)
{
        return Map->dimy;
}
