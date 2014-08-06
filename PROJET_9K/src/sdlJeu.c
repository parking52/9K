#define _BSD_SOURCE
#include <fmodex/fmod.h>
#include <assert.h>
#include "sdlJeu.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "Jeu.h"

const int TAILLE_SPRITE=32;

void sdljeuInit(sdlJeu *sdlj)
{
        Jeu *j;
        int dimx, dimy;
	sdlj->mode = 0;
	
        TTF_Init(); /* Initialisation de SDL_ttf */
        if (TTF_Init() == -1)
        {
                fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
                exit(EXIT_FAILURE);
        }
        sdlj->police = TTF_OpenFont( "/usr/share/fonts/truetype/freefont/FreeSansBold.ttf", 28 ); /* Ouverture de la police */
	assert(sdlj->police!=NULL);
        TTF_SetFontStyle(sdlj->police, TTF_STYLE_ITALIC);
	
        j = &(sdlj->j);
        jeuInit(j);

        assert(SDL_Init( SDL_INIT_EVERYTHING )!=-1);

        dimx = mapDimX(jeuGetConstMapPtr(j));
        dimy = mapDimY(jeuGetConstMapPtr(j));
        dimx = dimx * TAILLE_SPRITE;
        dimy = dimy * TAILLE_SPRITE;
	
        sdlj->surface_ecran = SDL_SetVideoMode(dimx, dimy, 32, SDL_SWSURFACE); /* déclaration de la fenêtre SDL */
        assert(sdlj->surface_ecran!=NULL);
        SDL_WM_SetCaption("9K", NULL);
	/* Chargement des images du jeu (pas celles des menus) */
        sdlj->surface_9K = SDL_load_image("data/Leonidas_projet.bmp");
        if (sdlj->surface_9K==NULL)
        {
                sdlj->surface_9K = SDL_load_image("../data/Leonidas_projet.bmp");
        }
        assert(sdlj->surface_9K!=NULL);

        sdlj->surface_sable = SDL_load_image("data/sable.bmp");
        if (sdlj->surface_sable==NULL)
        {
                sdlj->surface_sable = SDL_load_image("../data/sable.bmp");
        }
        assert(sdlj->surface_sable!=NULL);
	
	sdlj->surface_javelot = SDL_load_image("data/javelot.bmp");
        if (sdlj->surface_javelot==NULL)
        {
                sdlj->surface_javelot = SDL_load_image("../data/javelot.bmp");
        }
        assert(sdlj->surface_javelot!=NULL);
	
	
}

void sdljeuAff(sdlJeu * sdlj)
{
        int x,y,i;
	char pdv[2];
	char scorechar[5];
	SDL_Color Blanc = {255, 255, 255};
        const map *Map = jeuGetConstMapPtr(&(sdlj->j));
        const Leonidas *leo = jeuGetConstLeonidasPtr(&(sdlj->j));
	sprintf(pdv, "%d", sdlj->j.leo.hp);
	sprintf(scorechar, "%d", sdlj->j.TabE.score-1);
	sdlj->surface_score_hp = TTF_RenderText_Blended(sdlj->police, "Score :               HP : ", Blanc);
	sdlj->surface_nbScore = TTF_RenderText_Blended(sdlj->police, scorechar, Blanc);
	sdlj->surface_nbHp = TTF_RenderText_Blended(sdlj->police, pdv, Blanc);
	
        /* Remplir l'écran de noir */
        SDL_FillRect(sdlj->surface_ecran, &sdlj->surface_ecran->clip_rect, SDL_MapRGB(sdlj->surface_ecran->format, 0x00, 0x00, 0x00 ) );

        for (x=0;x<mapDimX(Map);++x)
        {
                for (y=0;y<mapDimY(Map);++y)
                {
                        if (mapGetXY(Map,x,y)=='.')
                        {
                                SDL_apply_surface(sdlj->surface_sable, sdlj->surface_ecran, x*TAILLE_SPRITE, y*TAILLE_SPRITE);/* affiche la map*/
                        }
                }
        }
	
        /* Copie des sprites sur l'écran */
        SDL_apply_surface(sdlj->surface_9K, sdlj->surface_ecran, leoGetX(leo)*TAILLE_SPRITE,  leoGetY(leo)*TAILLE_SPRITE );
	
	SDL_apply_surface(sdlj->surface_score_hp,sdlj->surface_ecran, 8*TAILLE_SPRITE, 20*TAILLE_SPRITE );
	SDL_FreeSurface(sdlj->surface_score_hp);
	
	SDL_apply_surface(sdlj->surface_nbScore,sdlj->surface_ecran, 9*TAILLE_SPRITE, 21*TAILLE_SPRITE );
	SDL_FreeSurface(sdlj->surface_nbScore);
	
	SDL_apply_surface(sdlj->surface_nbHp,sdlj->surface_ecran, 16*TAILLE_SPRITE, 21*TAILLE_SPRITE );
	SDL_FreeSurface(sdlj->surface_nbHp);
	
	
	for(i=0;i<JeuGetNbEnn(&(sdlj->j));i++)
        {
                const Ennemi *enn = jeuGetConstEnnemiPtr(&(sdlj->j),i);/* obtenir le pointeur de l'ennemi dans le tableau d'ennemi*/
                SDL_apply_surface(sdlj->surface_javelot, sdlj->surface_ecran, enn->x*TAILLE_SPRITE, enn->y*TAILLE_SPRITE);/* copie le sprite de l'ennemi i sur l'écran */
        }
}

void sdljeuDetruit(sdlJeu * sjeu)
{
	SDL_FreeSurface(sjeu->surface_9K);
	SDL_FreeSurface(sjeu->surface_sable);
	SDL_FreeSurface(sjeu->surface_javelot);
	TTF_CloseFont(sjeu->police);
	TTF_Quit();
	SDL_Quit();
}

void sdljeuBoucle(sdlJeu * sdlj)
{
	sdljeuInit(sdlj);
        SDL_Event event;
	SDL_Event terminerJeu;
	int recommencer = 0;
        int continue_boucle = 1;
	int continue_boucle1 = 1;
	int continue_boucle2 = 1;
	int jouer = 0;
	SDL_Color Blanc = {255, 255, 255};
	
	/*	MENU	*/
	
	/*	SON_MENU	*/
	
	FMOD_SYSTEM *sys;
	FMOD_SOUND *madness;
	FMOD_RESULT result;
	FMOD_System_Create(&sys);
	FMOD_System_Init(sys, 1, FMOD_INIT_NORMAL, NULL);

	/* On ouvre la musique */
	result = FMOD_System_CreateSound(sys, "../data/intro.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &madness);
	
	/* On vérifie si elle a bien été ouverte */
	if (result != FMOD_OK)
	{
		fprintf(stderr, "Impossible de lire le fichier mp3\n");
		exit(EXIT_FAILURE);
	}
	/* On joue la musique */
	FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, madness, 0, NULL);
	
	SDL_Event menu;
	int continue_menu = 1;
	sdlj->surface_imgmenu = SDL_load_image("data/mdj9K.bmp");
	if(sdlj->surface_imgmenu == NULL)
	{
		sdlj->surface_imgmenu = SDL_load_image("../data/mdj9K.bmp");
	}
	assert(sdlj->surface_imgmenu!=NULL);
	
	SDL_apply_surface(sdlj->surface_imgmenu, sdlj->surface_ecran, 3*TAILLE_SPRITE, 3*TAILLE_SPRITE );
	SDL_Flip(sdlj->surface_ecran);
	while (continue_menu == 1)
	{
		while (SDL_PollEvent( &menu ) )
		{
			 if ( menu.type == SDL_QUIT )
			 {
				exit(EXIT_SUCCESS);
			 }
			else if ( menu.type == SDL_MOUSEBUTTONUP )
			{
				if (menu.button.button == SDL_BUTTON_LEFT)
				{
					if(menu.button.x>=16.5*TAILLE_SPRITE && menu.button.x<=22*TAILLE_SPRITE && menu.button.y>=16*TAILLE_SPRITE && menu.button.y<=17*TAILLE_SPRITE)
					{	/* choix du mode illimité */
						sdlj->mode = 1;
						jouer = 1;
						continue_menu = 0;
					}
					else if(menu.button.x>=5*TAILLE_SPRITE && menu.button.x<=11*TAILLE_SPRITE && menu.button.y>=16*TAILLE_SPRITE && menu.button.y<=17*TAILLE_SPRITE)
					{
						/* choix du mode classique */
						sdlj->mode = 2;
						jouer = 1;
						continue_menu = 0;
					}
				}
			}
		}
	}
	SDL_FreeSurface(sdlj->surface_imgmenu);
	FMOD_Sound_Release(madness);
	FMOD_System_Close(sys);
	FMOD_System_Release(sys);
	
	/*	Si on a décider de jouer	*/
	if(jouer==1)
	{
		/*	MUSIQUE_JEU	*/
		
		FMOD_SYSTEM *system;
		FMOD_SOUND *musique;
		FMOD_RESULT resultat;
		FMOD_System_Create(&system);
		FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

		/* On ouvre la musique */
		resultat = FMOD_System_CreateSound(system, "../data/musique_jeu.mp3", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
		
		/* On vérifie si elle a bien été ouverte */
		if (resultat != FMOD_OK)
		{
			fprintf(stderr, "Impossible de lire le fichier mp3\n");
			exit(EXIT_FAILURE);
		}

		/* On active la répétition de la musique à l'infini */
		FMOD_Sound_SetLoopCount(musique, -1);

		/* On joue la musique */
		FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);

		sdljeuAff(sdlj);
		assert(SDL_Flip(sdlj->surface_ecran )!=-1);

		/*****************MODE ILLIMITE*****************/
		
		if(sdlj->mode==1)
		{
			 while ( continue_boucle == 1 )
			{
				/* tant qu'il y a des evenements à traiter : cette boucle n'est pas bloquante */
				while ( SDL_PollEvent( &event ) )
				{
					/* Si l'utilisateur a cliqué sur la croix de fermeture */
					if ( event.type == SDL_QUIT )
						continue_boucle = 0;

					/* Si l'utilisateur a appuyé sur une touche */
					if ( event.type == SDL_KEYDOWN )
					{
						switch ( event.key.keysym.sym )
						{
							case SDLK_UP:
								jeuActionClavier( &(sdlj->j), 'h');
							break;
							case SDLK_DOWN:
								jeuActionClavier( &(sdlj->j), 'b');
							break;
							case SDLK_LEFT:
								jeuActionClavier( &(sdlj->j), 'g');
							break;
							case SDLK_RIGHT:
								jeuActionClavier( &(sdlj->j), 'd');
							break;
							default: break;
						}
					}
				}
				
				temps_jeu_illimite(&(sdlj->j));
					
				/* on affiche le jeu sur le buffer caché */
				sdljeuAff(sdlj);

				/* on permute les deux buffers */
				SDL_Flip(sdlj->surface_ecran);
				
				sdlj->finalscore = sdlj->j.TabE.score-1;
				
				/*	Si le joueur perd (hp =0)	*/
				if(sdlj->j.leo.hp<1)
				{	
					/* On remplit l'écran de noir */
					SDL_FillRect(sdlj->surface_ecran, &sdlj->surface_ecran->clip_rect, SDL_MapRGB(sdlj->surface_ecran->format, 0x00, 0x00, 0x00 ) );
					
					char finalscore[6];
					sprintf(finalscore, "%d", sdlj->finalscore);
					sdlj->surface_finalscore = TTF_RenderText_Blended(sdlj->police, finalscore , Blanc);
					sdlj->surface_ill_texte = TTF_RenderText_Blended(sdlj->police, "Votre score est de : " , Blanc);
					
					sdlj->surface_imgd = SDL_load_image("../data/ill9K.bmp");
					if(sdlj->surface_imgd == NULL)
					{
						sdlj->surface_imgd = SDL_load_image("../data/ill9K.bmp");
					}
					assert(sdlj->surface_imgd!=NULL);
					/* On affiche les nouvelles informations */
					SDL_apply_surface(sdlj->surface_ill_texte, sdlj->surface_ecran, 10*TAILLE_SPRITE, 19*TAILLE_SPRITE );
					SDL_apply_surface(sdlj->surface_finalscore, sdlj->surface_ecran, 11*TAILLE_SPRITE, 20*TAILLE_SPRITE );
					SDL_apply_surface(sdlj->surface_imgd, sdlj->surface_ecran, 3*TAILLE_SPRITE,  3*TAILLE_SPRITE );
					/* On permute les deux buffers */
					SDL_Flip(sdlj->surface_ecran);
					
					FMOD_Sound_Release(musique);
					FMOD_System_Close(system);
					FMOD_System_Release(system);
					
					/*	SON_FIN		*/
					
					FMOD_SYSTEM *sy;
					FMOD_SOUND *hell;
					FMOD_RESULT resu;
					FMOD_System_Create(&sy);
					FMOD_System_Init(sy, 1, FMOD_INIT_NORMAL, NULL);

					/* On ouvre la musique */
					resu = FMOD_System_CreateSound(sy, "../data/hellok.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &hell);
					
					/* On vérifie si elle a bien été ouverte */
					if (resu != FMOD_OK)
					{
						fprintf(stderr, "Impossible de lire le fichier mp3\n");
						exit(EXIT_FAILURE);
					}

					FMOD_System_PlaySound(sy, FMOD_CHANNEL_FREE, hell, 0, NULL);
					
						
					while(continue_boucle2==1)
					{
						while (SDL_PollEvent( &terminerJeu ) )
						{
							 if ( terminerJeu.type == SDL_QUIT )/* On clique sur la croix : on quiite le jeu */
							 {
								exit(EXIT_SUCCESS);
							 }
							else if ( terminerJeu.type == SDL_MOUSEBUTTONUP )
							{
								if (terminerJeu.button.button == SDL_BUTTON_LEFT)
								{
									if(terminerJeu.button.x>=6*TAILLE_SPRITE && terminerJeu.button.x<=21*TAILLE_SPRITE && terminerJeu.button.y>=14*TAILLE_SPRITE && terminerJeu.button.y<=15.5*TAILLE_SPRITE)
									{
										/*	On a choisit de relancer le jeu	*/
										SDL_FreeSurface(sdlj->surface_imgd);
										SDL_FreeSurface(sdlj->surface_finalscore);
										SDL_FreeSurface(sdlj->surface_ill_texte);
										sdlj->surface_imgd = NULL;
										recommencer =1;
										sdljeuDetruit(sdlj);
										/* On a libérer tout ce qu'il fallait pour relancer le jeu de manière propre */
										sdljeuBoucle(sdlj);/* appel réccursif pour rejouer */
									}
								}
							}
						}
					}
					FMOD_Sound_Release(hell);
					FMOD_System_Close(sy);
					FMOD_System_Release(sy);
				}
			}
		}
		
	     /*************************MODE CLASSIQUE***********************/

		if(sdlj->mode==2)
		{
			while ( continue_boucle == 1 )
			{
				/* tant qu'il y a des evenements à traiter : cette boucle n'est pas bloquante */
				while ( SDL_PollEvent( &event ) )
				{
					/* Si l'utilisateur a cliqué sur la croix de fermeture */
					if ( event.type == SDL_QUIT )
						continue_boucle = 0;

					/* Si l'utilisateur a appuyé sur une touche */
					if ( event.type == SDL_KEYDOWN )
					{
						switch ( event.key.keysym.sym )
						{
							case SDLK_UP:
								jeuActionClavier( &(sdlj->j), 'h');
							break;
							case SDLK_DOWN:
								jeuActionClavier( &(sdlj->j), 'b');
							break;
							case SDLK_LEFT:
								jeuActionClavier( &(sdlj->j), 'g');
							break;
							case SDLK_RIGHT:
								jeuActionClavier( &(sdlj->j), 'd');
							break;
							default: break;
						}
					}				
				}
				
				
				temps_jeu(&(sdlj->j));
					
				/* on affiche le jeu sur le buffer caché */
				sdljeuAff(sdlj);

				/* on permute les deux buffers */
				SDL_Flip(sdlj->surface_ecran);
				
				/* Si le joueur gagne (score>9000)*/
				if(sdlj->j.TabE.score>9001)
				{
					/* On remplit l'écran de noir */
					SDL_FillRect(sdlj->surface_ecran, &sdlj->surface_ecran->clip_rect, SDL_MapRGB(sdlj->surface_ecran->format, 0x00, 0x00, 0x00 ) );
					sdlj->surface_imgd = SDL_load_image("../data/idv9K.bmp");
					if(sdlj->surface_imgd == NULL)
					{
						sdlj->surface_imgd = SDL_load_image("../data/idv9K.bmp");
					}
					assert(sdlj->surface_imgd!=NULL);
					/* On affiche la nouvelle image */
					SDL_apply_surface(sdlj->surface_imgd, sdlj->surface_ecran, 3*TAILLE_SPRITE,  3*TAILLE_SPRITE );
					/* On permute les deux buffers */
					SDL_Flip(sdlj->surface_ecran);
						
					FMOD_Sound_Release(musique);
					FMOD_System_Close(system);
					FMOD_System_Release(system);
					
					/*	SON_VICTOIRE	*/
		
					FMOD_SYSTEM *syst;
					FMOD_SOUND *over9k;
					FMOD_RESULT res;
					FMOD_System_Create(&syst);
					FMOD_System_Init(syst, 1, FMOD_INIT_NORMAL, NULL);

					/* On ouvre la musique */
					res = FMOD_System_CreateSound(syst, "../data/ITSOVER9000.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &over9k);
					
					/* On vérifie si elle a bien été ouverte */
					if (res != FMOD_OK)
					{
						fprintf(stderr, "Impossible de lire le fichier mp3\n");
						exit(EXIT_FAILURE);
					}

					FMOD_System_PlaySound(syst, FMOD_CHANNEL_FREE, over9k, 0, NULL);
						
					while(continue_boucle1==1)
					{
						
						while (SDL_PollEvent( &terminerJeu ) )
						{
							 if ( terminerJeu.type == SDL_QUIT )/* on clique sur la croix : on quiite le jeu */
							 {
								exit(EXIT_SUCCESS);
							 }
							else if ( terminerJeu.type == SDL_MOUSEBUTTONUP )
							{
								if (terminerJeu.button.button == SDL_BUTTON_LEFT)
								{
									if(terminerJeu.button.x>=10*TAILLE_SPRITE && terminerJeu.button.x<=17*TAILLE_SPRITE && terminerJeu.button.y>=17*TAILLE_SPRITE && terminerJeu.button.y<=18*TAILLE_SPRITE)
									{	
										/* on a choisit de rejouer */
										SDL_FreeSurface(sdlj->surface_imgd);
										sdlj->surface_imgd = NULL;
										recommencer =1;
										sdljeuDetruit(sdlj);
										/* On a libérer tout ce qu'il fallait pour relancer le jeu de manière propre */
										sdljeuBoucle(sdlj);/* appel réccursif pour rejouer */
									}
								}
							}
						}
					}
					FMOD_Sound_Release(over9k);
					FMOD_System_Close(syst);
					FMOD_System_Release(syst);
				}
				else if(sdlj->j.leo.hp<1) /* Si le joueur perd (hp=0) */
				{
					/* On remlit l'ecran de noir */
					SDL_FillRect(sdlj->surface_ecran, &sdlj->surface_ecran->clip_rect, SDL_MapRGB(sdlj->surface_ecran->format, 0x00, 0x00, 0x00 ) );
					sdlj->surface_imgd = SDL_load_image("../data/idd9K.bmp");
					if(sdlj->surface_imgd == NULL)
					{
						sdlj->surface_imgd = SDL_load_image("../data/idd9K.bmp");
					}
					assert(sdlj->surface_imgd!=NULL);
					/* On affiche les nouvelles informations */
					SDL_apply_surface(sdlj->surface_imgd, sdlj->surface_ecran, 3*TAILLE_SPRITE,  3*TAILLE_SPRITE );
					/* on permute les deux buffers */
					SDL_Flip(sdlj->surface_ecran);
						
					FMOD_Sound_Release(musique);
					FMOD_System_Close(system);
					FMOD_System_Release(system);
					
					/*	SON GAME OVER	*/
		
					FMOD_SYSTEM *s;
					FMOD_SOUND *gameover;
					FMOD_RESULT r;
					FMOD_System_Create(&s);
					FMOD_System_Init(s, 1, FMOD_INIT_NORMAL, NULL);

					/* On ouvre le son */
					r = FMOD_System_CreateSound(s, "../data/game_over.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &gameover);
					
					/* On vérifie si elle a bien été ouverte */
					if (r != FMOD_OK)
					{
						fprintf(stderr, "Impossible de lire le fichier mp3\n");
						exit(EXIT_FAILURE);
					}

					/* On joue le son */
					FMOD_System_PlaySound(s, FMOD_CHANNEL_FREE, gameover, 0, NULL);
						
					while(continue_boucle2==1)
					{
						while (SDL_PollEvent( &terminerJeu ) )
						{
							 if ( terminerJeu.type == SDL_QUIT )/* On quitte le jeu : on clique sur la croix */
							 {
								exit(EXIT_SUCCESS);
							 }
							else if ( terminerJeu.type == SDL_MOUSEBUTTONUP )
							{
								if (terminerJeu.button.button == SDL_BUTTON_LEFT)
								{
									if(terminerJeu.button.x>=11*TAILLE_SPRITE && terminerJeu.button.x<=16*TAILLE_SPRITE && terminerJeu.button.y>=16*TAILLE_SPRITE && terminerJeu.button.y<=17*TAILLE_SPRITE)
									{
										/* On a choisit de rejouer */
										SDL_FreeSurface(sdlj->surface_imgd);
										sdlj->surface_imgd = NULL;
										recommencer =1;
										sdljeuDetruit(sdlj);
										/* On a libérer tout ce qu'il fallait pour relancer le jeu de manière propre */
										sdljeuBoucle(sdlj);/* appel réccursif pour rejouer */
									}
								}
							}
						}
					}
					FMOD_Sound_Release(gameover);
					FMOD_System_Close(s);
					FMOD_System_Release(s);
				}
			}
		}
	}
}


SDL_Surface *SDL_load_image(const char* filename)
{
	/* Tampon pour l'image qui est chargée */
	SDL_Surface* loadedImage = NULL;
	/* L'image optimisée qui va être utilisée*/
	SDL_Surface* optimizedImage = NULL;
	/* Chargement de l'image */
	loadedImage = SDL_LoadBMP( filename);
	if ( loadedImage != NULL )
	{
		/* Création d'une image optimisée */
		optimizedImage = SDL_DisplayFormat( loadedImage );
		/* Free l'ancienne image */
		SDL_FreeSurface( loadedImage );
	}
	/* Renvoie l'image optimisée */
	return optimizedImage;
}


void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y )
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	/* Applique la surface */
	SDL_BlitSurface( source, NULL, destination, &offset );
}

