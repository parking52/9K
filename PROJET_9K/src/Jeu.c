#define _BSD_SOURCE
#include "Jeu.h"
#include "stdlib.h"
#include "assert.h"
#include "ncursJeu.h"
#include <math.h>
#include <ncurses.h>
#include "sdlJeu.h"
#include <sys/time.h>
#include <time.h>

void jeuInit(Jeu *j)
{
        int a=0;
	j->intervalle=1000;
        leoInit(&(j->leo));
        mapInit(&(j->map));
        tabennInit(&(j->TabE),a);
}

map *jeuGetMapPtr(Jeu *j)
{
        return &(j->map);
}

int JeuGetNbEnn(const Jeu *j)
{
        int i;
        int a=0;
        for(i=0;i<j->TabE.taille;i++)
        {
                if(j->TabE.Tenn[i]!=NULL)
                {
                        a++;
                }
        }
        return a;
}

Leonidas *jeuGetLeonidasPtr(Jeu *j)
{
        return &(j->leo);
}

Ennemi *jeuGetEnnemiPtr(Jeu *j, int a)
{
       return j->TabE.Tenn[a];
}

const Ennemi *jeuGetConstEnnemiPtr(const Jeu *j, int a)
{
        int i;
        for(i=0;i<j->TabE.taille;i++)
        {
                if(j->TabE.Tenn[i]!=NULL)
                {
                        if(a==0)
                        {
                               return j->TabE.Tenn[i]; 
                        }
                        else
                        {
                                a--;
                        }
                }
        }
        assert(0);
}

const map *jeuGetConstMapPtr(const Jeu *j)
{
        return &(j->map);
}

const Leonidas *jeuGetConstLeonidasPtr(const Jeu *j)
{
        return &(j->leo);
}


void jeuActionClavier(Jeu *j, const char touche)
{
        switch(touche)
        {
                case 'g' :
                        leoGauche(&(j->leo), &(j->map));
                        collision_leo(&(j->TabE), &(j->leo));
                break;
                case 'd' :
                        leoDroite(&(j->leo), &(j->map));
                        collision_leo(&(j->TabE), &(j->leo));
                break;
                case 'h' :
                        leoHaut(&(j->leo), &(j->map));
                        collision_leo(&(j->TabE), &(j->leo));
                break;
                case 'b' :
                        leoBas(&(j->leo), &(j->map));
                        collision_leo(&(j->TabE), &(j->leo));
                break;
        }
}

int temps_jeu(Jeu *j)
{
	struct timeval temps_actuel, temps_difference;
	gettimeofday(&temps_actuel, 0);
	timersub(&temps_actuel, &j->temps_precedent, &temps_difference);
	if (temps_difference.tv_usec/1000+temps_difference.tv_sec*1000>=j->intervalle)
	{
		/* creer ennemi */
		ennTour(&(j->TabE), &(j->map), &(j->leo));
		newWave(&(j->TabE));

		j->temps_precedent  = temps_actuel;
		j->intervalle = 1000-(j->TabE.score/10);
		return 1;
	}
	return 0;	
}

int temps_jeu_illimite(Jeu *j)
{
	struct timeval temps_actuel, temps_difference;
	gettimeofday(&temps_actuel, 0);
	timersub(&temps_actuel, &j->temps_precedent, &temps_difference);
	if (temps_difference.tv_usec/1000+temps_difference.tv_sec*1000>=j->intervalle)
	{
		/* creer ennemi */
		ennTour(&(j->TabE), &(j->map), &(j->leo));
		newWave(&(j->TabE));

		j->temps_precedent  = temps_actuel;
		j->intervalle = 400;
		return 1;
	}
	return 0;	
}

