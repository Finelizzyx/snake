#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#include "snake.h"

int main (int argc, char *argv[]) {

	/* variable declarations */
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img = NULL;
	int w, h; /* texture width & height */
	SDL_Rect texr;
	int direction;
	int c = 0;
	int vitesse = 1000;
	int continuer = 1;
	Snake *snake = NULL;


    srand(time(NULL));

	/* Initialize SDL. */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return 1;

	/* create the window and renderer
	 note that the renderer is accelerated */
	win = SDL_CreateWindow("Snake", 100, 100, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	/* load our image */
	img = IMG_LoadTexture(renderer, IMG_PATH);
	SDL_QueryTexture(img, NULL, NULL, &w, &h); /* get the width and height of the texture */
	/* put the location where we want the texture to be drawn into a rectangle
     I'm also scaling the texture 2x simply by setting the width and height */

    direction = rand()%4;
    texr.x = rand()%(WIDTH + 1 - w);
    texr.y = rand()%(HEIGHT + 1 - h);
    texr.w = w;
    texr.h = h;

    snake = (Snake*)malloc(sizeof(Snake));

    snake->img = img;
    snake->r->x = texr.x;
    snake->r->y = texr.y;
    snake->r->w = texr.w;
    snake->r->h = texr.h;
    snake->suivant = NULL;

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
            switch(direction)
            {
                case DROITE:
                    snake->r->x += w;
                    break;
                case GAUCHE:
                    snake->r->x -= w;
                    break;
                case BAS:
                    snake->r->y += h;
                    break;
                case HAUT:
                    snake->r->y -= h;
                    break;
            }
            c = 0;
        }
        else c++;

	}

	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
    free(snake);
	return 0;
}

void afficherImage(SDL_Renderer *renderer, SDL_Texture *img, SDL_Rect *r)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, img, NULL, r);
    SDL_RenderPresent(renderer);
}

void afficherSerpent(SDL_Renderer *renderer, Snake *snake)
{
    Snake *snakeTemp = snake;

    while(snakeTemp != NULL)
    {
        afficherImage(renderer, snakeTemp->img, snakeTemp->r);
        snakeTemp = snakeTemp->suivant;
    }
}
