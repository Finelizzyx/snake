#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#define MAINFILE

#include "snake.h"

int main (int argc, char *argv[]) {

    Point *pt;
    Point *ptsuivant;

	/* variable declarations */
	win = NULL;
	renderer = NULL;
	img = NULL;
	c = 0;
	vitesse = 1000;
	continuer = 1;
	snake = NULL;

    srand(time(NULL));

	/* Initialize SDL. */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return 1;

	/* create the window and renderer
	 note that the renderer is accelerated */
	win = SDL_CreateWindow("Snake", 100, 100, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


    snake = initSerpent(renderer);

    direction = rand()%4;

    points = AfficherPoints(renderer, NIVEAU1_PATH);

	while (continuer) {

		/* event handling */
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
                            direction = HAUT;
                            break;
                        case SDLK_DOWN:
                            direction = BAS;
                            break;
                        case SDLK_RIGHT:
                            direction = DROITE;
                            break;
                        case SDLK_LEFT:
                            direction = GAUCHE;
                            break;

                    }
            }

		}

        afficherSerpent(renderer, snake);

        if(c == vitesse)
        {
            Serpent(snake, dir);
            c = 0;
        }
        else c++;

	}

	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
    free(snake);

    pt = points->premier;
    while(pt != NULL) {
        ptsuivant = pt->suivant;
        SDL_DestroyTexture(pt->img);
        free(pt);
        pt = ptsuivant;
    }
    free(points);

	return 0;
}
