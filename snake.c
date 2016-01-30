/** #########################################
Fonction main
############################################
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#define MAINFILE

#include "snake.h"

int main (int argc, char *argv[])
{
	/* déclaration des variables*/
	win = NULL;
	renderer = NULL;
	continuer = SDL_TRUE;
	snake = NULL;
	points = NULL;
	tempsActuel = 0;
	tempsPrecedent = 0;
	niveauActuel = 1;
	pause = SDL_FALSE;
	gagner = SDL_FALSE;

    srand(time(NULL));

	/* Initialisation de la SDL. */
	init();

	/* Création de la fenêtre et du renderer */
	win = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	/* Création de la police */
	if((police = TTF_OpenFont("data/arial.ttf", 14)) == NULL)
        snakeERROR("Impossible d'ouvrir le fichier data/arial.ttf : %s\n", TTF_GetError());


    snake = initSerpent(renderer);
    ajouterSerpent(snake, renderer);
    points = initPoints();
    chargerPoints(points, niveauActuel);

    afficherPoints(renderer, points);
    afficherSerpent(renderer, snake);

	while(continuer)
    {
		SDL_Event e;
		if(SDL_PollEvent(&e)) {
            switch(e.type)
            {
                case SDL_QUIT:
                    continuer = SDL_FALSE;
                    break;
                case SDL_KEYUP:
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                        continuer = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            snake->direction = HAUT;
                            break;
                        case SDLK_DOWN:
                            snake->direction = BAS;
                            break;
                        case SDLK_RIGHT:
                            snake->direction = DROITE;
                            break;
                        case SDLK_LEFT:
                            snake->direction = GAUCHE;
                            break;
                        case SDLK_p:
                            if(pause)
                            {
                                pause = SDL_FALSE;
                                SDL_RenderFillRect(renderer, &rectPause);
                            }
                            else
                            {
                                pause = SDL_TRUE;
                                rectPause = afficherTexte(renderer, "PAUSE", police, 400, 300, 255, 255, 255);
                            }
                            break;
                    }
            }
		}

        tempsActuel = SDL_GetTicks();
        if(tempsActuel - tempsPrecedent > INTERVALLE && !pause) /* Si 0.2 sec se sont écoulées */
        {
            deplacerSerpent(snake, renderer);
            afficherSerpent(renderer, snake);
            afficherPoints(renderer, points);
            if(pointsVide(points))
            {
                /* Il reste des niveaux à faire */
                if(niveauActuel < MAX_NIVEAUX)
                    chargerPoints(points, ++niveauActuel);
                /* On a fini tous les niveaux */
                else
                {
                    continuer = SDL_FALSE;
                    gagner = SDL_TRUE;
                    afficherTexte(renderer, "Gagné !", police, 400, 300, 255, 255, 255);
                }
            }
            tempsPrecedent = tempsActuel;
        }
	}

	quit();

	return EXIT_SUCCESS;
}
