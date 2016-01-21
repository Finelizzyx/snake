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
	continuer = 1;
	snake = NULL;
	tempsActuel = 0;
	tempsPrecedent = 0;

    srand(time(NULL));

	/* Initialisation de la SDL. */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

	/* Création de la fenêtre et du renderer */
	win = SDL_CreateWindow("Snake", 100, 100, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    snake = initSerpent(renderer);
    ajouterSerpent(snake, renderer);
    points = initPoints();
    chargerPoints(points, NIVEAU1_PATH);

    afficherPoints(renderer, points);
    afficherSerpent(renderer, snake);

	while (continuer)
    {
		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
            switch(e.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYUP:
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                        continuer = 0;
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
                    }
            }
		}

        tempsActuel = SDL_GetTicks();
        if(tempsActuel - tempsPrecedent > INTERVALLE) /* Si 30 ms se sont écoulées */
        {
            deplacerSerpent(snake, renderer);
            afficherSerpent(renderer, snake);
            afficherPoints(renderer, points);
            if(pointsVide(points))
                chargerPoints(points, NIVEAU2_PATH);
            tempsPrecedent = tempsActuel;
        }
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
    libererSerpent(snake);
    libererPoints(points);

    SDL_Quit();

	return 0;
}
