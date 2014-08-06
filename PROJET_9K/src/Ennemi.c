#include "Leonidas.h"
#include "Ennemi.h"
#include "stdlib.h"


const int ennemi_par_vague=5;

void ennInit(Ennemi *enn)
{
        enn->y=0;
        enn->x=(float)15*rand()/RAND_MAX;
        enn->age=0;
}

void tabennInit(Tableau_ennemi *Te, int a)
{
        int i;
        Te->taille=225;
        Te->score=1;
        Te->Tenn=(Ennemi**)malloc(Te->taille*sizeof(Ennemi*));
        for(i=0;i<Te->taille;i++)
        {
                Te->Tenn[i]=NULL;
        }
}

void ennBas(Ennemi *enn, const map *Map)
{
	enn->y++;
}

void libereEnnemi(Tableau_ennemi *Te, int i)
{
        free(Te->Tenn[i]); 
        Te->Tenn[i]=NULL;
}

void libererToutEnnemi(Tableau_ennemi *Te)
{
	int i;
	i=225;
	for(i=0;i<225;i++)
	{
		free(Te->Tenn[i]);
		Te->Tenn[i]=NULL;
	}
}

void ennTour(Tableau_ennemi *Te, const map *Map, Leonidas *leo)/*fait descendre tous les ennemis du tableau*/
{
        int i;
        for(i=0;i<Te->taille;i++)
        {
                if(Te->Tenn[i]!=NULL)
                {
                        ennBas(Te->Tenn[i], Map);
                        incrementeAge(Te->Tenn[i]);
                        collision_enn(Te, i, leo);
                }
        }
        testAge(Te);
}

int ennGetX(const Ennemi *enn)
{
        if(enn!=NULL)
        {
                return enn->x;
        }
        else
        {
                return 0;
        }
}

int ennGetY(const Ennemi *enn)
{
        if(enn!=NULL)
        {
                return enn->y;
        }
        else
        {
                return 0;
        }
}

void ajouteEnnemi(Tableau_ennemi *Te)
{
        Ennemi *enn;
        enn=(Ennemi*)malloc(sizeof(Ennemi));
        ennInit(enn);
        ajouteEnnemiDansTableau(Te,enn);
}

void ajouteEnnemiDansTableau(Tableau_ennemi *Te,Ennemi *enn)
{
        int i;
        i=0;
        while (i<Te->taille && Te->Tenn[i]!=NULL)
                i++;
        
        if (i<Te->taille)
	{
                Te->Tenn[i]=enn;
	}
        else
	{
                /* Plus de place */
        }
}

void newWave(Tableau_ennemi *Te)
{
        int i;
        for(i=0;i<ennemi_par_vague;i++)
        {
                ajouteEnnemi(Te);
        }
}

void incrementeAge(Ennemi *enn) 
{
        enn->age=enn->age+1;
}

void testAge(Tableau_ennemi *Te)
{
        int i;
        for(i=0;i<Te->taille;i++)
        {
                if(Te->Tenn[i]!=NULL && Te->Tenn[i]->age>=15)
                {
                        Te->score=Te->score+20;/* le score c'est comme compter le nombre d'ennemi qui arrive en bas et qu'on "free" */
                        libereEnnemi(Te, i);
                }
        }
}



void collision_enn(Tableau_ennemi *Te, int i, Leonidas *leo)
{
        if(Te->Tenn[i]->x == leo->x && Te->Tenn[i]->y == leo->y)
        {
                libereEnnemi(Te,i);
                leo->hp = leo->hp-1;
        }
}

void collision_leo(Tableau_ennemi *Te, Leonidas *leo)
{
        int i ;
        for(i=0;i<225;i++)
        {
                if(Te->Tenn[i]!=NULL && Te->Tenn[i]->x == leo->x && Te->Tenn[i]->y == leo->y)
                {
                        libereEnnemi(Te,i);
                        leo->hp = leo->hp-1;
                        break;
                }
        }
}