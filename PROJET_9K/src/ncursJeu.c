#define _BSD_SOURCE
#include <sys/time.h>
#include <stdio.h>
#ifdef WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif
#include "Jeu.h"
#include <time.h>

void ncursAff( WINDOW *win, const Jeu *j)
{
        int x,y;
        int i;
        const map *Map = jeuGetConstMapPtr(j);
        const Leonidas *leo = jeuGetConstLeonidasPtr(j);
        wclear(win);
        for(x=0;x<mapDimX(Map);x++)
        {
                for(y=0;y<mapDimY(Map);y++)
                {
                        mvwprintw(win, y, x, "%c", mapGetXY(Map,x,y));
                }
        }
        mvwprintw(win, leoGetY(leo), leoGetX(leo), "*");
        for(i=0;i<JeuGetNbEnn(j);i++)
        {
                const Ennemi *enn = jeuGetConstEnnemiPtr(j,i);/* obtenir le pointeur de l'ennemi dans le tableau d'ennemis*/
                mvwprintw(win, ennGetY(enn), ennGetX(enn), "#");
        }
        wmove(win, leoGetY(leo), leoGetX(leo));
}


void ncursBoucle(Jeu *j)
{
        WINDOW *win;
        int c;
        int continue_boucle;
        bool affichage;
        char a='a';
        initscr();		/* passe l'écran texte en mode NCurses */
        clear();		/* efface l'écran */
        noecho();  	/* Lorsqu'une touche est préssée au clavier, elle n'apparait pas à l'écran */
        cbreak();		/* un caractère est directement affiché, il ne passe pas dans un buffer */
        /* Creation d'une nouvelle fenetre en mode texte */
        win = newwin( mapDimY(jeuGetConstMapPtr(j))+20, mapDimX(jeuGetConstMapPtr(j))+20, 10, 5 );	
        keypad(win, TRUE);		/* pour que les flèches soient traitées */
        halfdelay( 0);
        notimeout(win,true);
        nodelay(win,true);
        continue_boucle = 1;
        
        ncursAff(win, j);

        do
        {
                mvwprintw(win, 24, 8, "HP :");
                mvwprintw(win, 24, 14, "%i\n", j->leo.hp);
                c=wgetch(win);
                switch(c)
                {	
                        case KEY_LEFT:
                                jeuActionClavier(j, 'g');
                                affichage=true;
                                ncursAff(win, j);
                        break;
                        case KEY_RIGHT:
                                jeuActionClavier(j, 'd');
                                affichage=true;
                                ncursAff(win, j);
                        break;
                        case KEY_UP:
                                jeuActionClavier(j, 'h');
                                affichage=true;
                                ncursAff(win, j);
                        break;
                        case KEY_DOWN:
                                jeuActionClavier(j, 'b');
                                affichage=true;
                                ncursAff(win, j);
                        break;
                        case 27: /* echap */
                                continue_boucle = 0;
                        break;
                }
		if (temps_jeu(j))
		{
			ncursAff(win, j);
		}
                mvwprintw(win, 25, 5, "Score : ");
                mvwprintw(win, 25, 14, "%i\n", j->TabE.score-1);
                if(j->TabE.score>9001)/* Si le joueur gagne */
                {
                        continue_boucle=0;
                        clear();
                        do
                        {
                                a=wgetch(win);
                                win = newwin(40,40,0,0);
                                mvwprintw(win, 10, 5, "IT'S OVER NINE THOUSAND !!!");
                        }
                        while(a!='e');
                        
                }
                else if(j->leo.hp<1)/* Si le joueur perd */
                {
                        continue_boucle=0;
                        clear();
                        do
                        {      a=wgetch(win);
                                win = newwin(40,40,0,0);
                                mvwprintw(win, 10, 5, "GAME OVER");
                        }
                        while(a!='e');
                }
                        
        } while (continue_boucle==1);
        endwin();
}
