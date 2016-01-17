/* #########################################
Gestion du serpent
############################################ */
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#include "snake.h"

Snakehead *initSerpent(SDL_Renderer *ecran)
{
    Snakehead *sh;
    Snake *s
    SDL_Texture *img;
    SDL_Rect *rect;

    if((sh = (Snakehead*)malloc(sizeof(Snakehead))) == NULL) { snakeERROR("ERROR - Erreur allocation mémoire !"); }
    if((s = (Snake*)malloc(sizeof(Snake)))  == NULL) { snakeERROR("ERROR - Erreur allocation mémoire !"); }
    if((rect = (SDL_Rect*)malloc(sizeof(SDL_Rect)))  == NULL) { snakeERROR("ERROR - Erreur allocation mémoire !"); }

	/* load our image */
	img = IMG_LoadTexture(ecran, IMG_ROND_PATH);
	SDL_QueryTexture(img, NULL, NULL, rect->w, rect->h); /* get the width and height of the texture */
	/* put the location where we want the texture to be drawn into a rectangle
     I'm also scaling the texture 2x simply by setting the width and height */

    rect->x = rand()%(WIDTH + 1 - rect.w);
    rect->y = rand()%(HEIGHT + 1 - rect.h);

    sh->premier = s;
    sh->nb = 1;
    s->img = img;
    s->r = rect;

    return sh;
}

void Serpent(Snakehead *snake, int dir) /*Tête vers la droite et glissement du reste du corps */
{
    Snake *snaketemp = snake->premier;
    int xprem = snaketemp->r->x;
    int yprem = snaketemp->r->y;
    snaketemp = snaketemp->suivant;

    while(snaketemp->suivant != NULL)
    {
        snaketemp->r->x = snaketemp->suivant->r->x;
        snaketemp->r->y = snaketemp->suivant->r->y;
        snaketemp = snaketemp->suivant;
    }

    switch(dir)
    {
        case DROITE:
            break;
        case GAUCHE:
            break;
        case HAUT:
            break;
        case BAS;
            break;
    }

}
