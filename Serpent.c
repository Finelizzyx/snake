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
    Snakehead *sh = NULL;
    Snake *s = NULL;
    SDL_Texture *img = NULL;
    SDL_Rect *rect;

    if((sh = (Snakehead*)malloc(sizeof(Snakehead))) == NULL) { snakeERROR("Erreur allocation mémoire !"); }
    if((s = (Snake*)malloc(sizeof(Snake)))  == NULL) { snakeERROR("Erreur allocation mémoire !"); }
    if((rect = (SDL_Rect*)malloc(sizeof(SDL_Rect)))  == NULL) { snakeERROR("Erreur allocation mémoire !"); }

    s->r = rect;
	/* load our image */
	img = IMG_LoadTexture(ecran, IMG_ROND_PATH);
	SDL_QueryTexture(img, NULL, NULL, &s->r->w, &s->r->h); /* get the width and height of the texture */
	/* put the location where we want the texture to be drawn into a rectangle
     I'm also scaling the texture 2x simply by setting the width and height */
    s->img = img;

    s->r->x = (rand()%(WIDTH/s->r->w)) * s->r->w;
    s->r->y = (rand()%(HEIGHT/s->r->h)) * s->r->h;
    s->suivant = NULL;

    sh->premier = s;
    sh->nb = 1;

    return sh;
}

void Serpent(Snakehead *snake, int dir) /*Tête vers la droite et glissement du reste du corps */
{
    Snake *snaketemp = snake->premier;

    SDL_RenderFillRect(renderer, snaketemp->r);

    while(snaketemp->suivant != NULL)
    {
        snaketemp->r->x = snaketemp->suivant->r->x;
        snaketemp->r->y = snaketemp->suivant->r->y;
        snaketemp = snaketemp->suivant;
    }

    switch(dir)
    {
        case DROITE:
            snaketemp->r->x += snaketemp->r->w;
            break;
        case GAUCHE:
            snaketemp->r->x -= snaketemp->r->w;
            break;
        case HAUT:
            snaketemp->r->y -= snaketemp->r->h;
            break;
        case BAS:
            snaketemp->r->y += snaketemp->r->h;
            break;
    }
    if(collisionPoint(snake, points)) { ajouterSerpent(snake, renderer); }

}

void ajouterSerpent(Snakehead *snake, SDL_Renderer *ecran)
{
    Snake *nouveau;
    SDL_Rect *rect;
    SDL_Texture *img;

    if((nouveau = (Snake*)malloc(sizeof(Snake))) == NULL) { snakeERROR("Erreur allocation mémoire !"); }
    if((rect = (SDL_Rect*)malloc(sizeof(SDL_Rect))) == NULL) { snakeERROR("Erreur allocation mémoire !"); }

    nouveau->r = rect;

    img = IMG_LoadTexture(ecran, IMG_ROND_PATH);
    SDL_QueryTexture(img, NULL, NULL, &nouveau->r->w, &nouveau->r->h);

    nouveau->img = img;

    nouveau->suivant = snake->premier;
    snake->premier = nouveau;
    snake->nb++;

}

void libererSerpent(Snakehead *snake)
{
    Snake *actuel = NULL;

    while(snake->premier != NULL)
    {
        actuel = snake->premier;
        snake->premier = snake->premier->suivant;
        SDL_DestroyTexture(actuel->img);
        free(actuel->r);
        free(actuel);
    }
    free(snake);
}

int collisionPoint(Snakehead *s, Points *p)
{
    Snake *snaketemp = s->premier;
    Point *pointemp  = p->premier;
    Point *pointprec = NULL;
    int collision = 0;

    /* Aller à la fin du serpent pour y trouver la tête */
    while(snaketemp->suivant != NULL) { snaketemp = snaketemp->suivant; }

    while(pointemp != NULL && collision == 0)
    {
        if(SDL_HasIntersection(snaketemp->r, pointemp->r))
        {
            collision = 1;
            if(pointprec == NULL) { p->premier = pointemp->suivant; } /* Il faut enlever le 1er élément */
            else { pointprec->suivant = pointemp->suivant; }

            SDL_DestroyTexture(pointemp->img);
            free(pointemp->r);
            free(pointemp);
            pointemp = NULL;
        }
        else
        {
            pointprec = pointemp;
            pointemp = pointemp->suivant;
        }
    }

    return collision;
}
