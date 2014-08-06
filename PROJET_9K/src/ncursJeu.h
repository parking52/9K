
#ifndef _NCURSJEU_H
#define _NCURSJEU_H
#ifdef WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include "Jeu.h"

/**
 *	\fn void ncursAff(WINDOW* win, const Jeu *j)
 *	\brief Fonction qui gère l'affichage du jeu en mode ncurses (texte), affichage des ennemis et du joueur 
 */
void ncursAff( WINDOW *win, const Jeu *j);

/**
 *	\fn void ncursBoucle(Jeu * j)
 *	\brief Fonction qui gère le déroulement du jeu en mode ncurses (texte)
 */
void ncursBoucle(Jeu * j);

#endif
