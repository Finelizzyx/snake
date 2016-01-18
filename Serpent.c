/* #########################################
Gestion du serpent
############################################ */
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#include "snake.h"

Snake *initSerpent(SDL_Renderer *renderer)
{
    Snake *snake = NULL;
    ElemSnake *elemSnake = NULL;

    if((snake = (Snake*)malloc(sizeof(Snake))) == NULL)
        snakeERROR("Erreur allocation mémoire !");

    snake->nb = 1;
    snake->direction = rand()%4; /* Donne une direction aléatoire à l'initialisation */

    if((elemSnake = (ElemSnake*)malloc(sizeof(ElemSnake)))  == NULL)
        snakeERROR("Erreur allocation mémoire !");

    if((elemSnake->r = (SDL_Rect*)malloc(sizeof(SDL_Rect)))  == NULL)
        snakeERROR("Erreur allocation mémoire !");

	/* chargement de l'image en fonction de la direction */
	switch(snake->direction)
	{
        case HAUT:
            elemSnake->img = IMG_LoadTexture(renderer, IMG_TETEH_PATH);
            break;
        case DROITE:
            elemSnake->img = IMG_LoadTexture(renderer, IMG_TETED_PATH);
            break;
        case BAS:
            elemSnake->img = IMG_LoadTexture(renderer, IMG_TETEB_PATH);
            break;
        case GAUCHE:
            elemSnake->img = IMG_LoadTexture(renderer, IMG_TETEG_PATH);
            break;
	}

	SDL_QueryTexture(elemSnake->img, NULL, NULL, &elemSnake->r->w, &elemSnake->r->h); /* récupère la hauteur et la largeur de la texture */

    elemSnake->r->x = (rand()%(WIDTH/elemSnake->r->w)) * elemSnake->r->w;
    elemSnake->r->y = (rand()%(HEIGHT/elemSnake->r->h)) * elemSnake->r->h;
    elemSnake->suivant = NULL;

    snake->premier = elemSnake;

    return snake;
}

void deplacerSerpent(Snake *snake) /*Tête dans la bonne direction et glissement du reste du corps */
{
    ElemSnake *snakeTemp = snake->premier;

    SDL_RenderFillRect(renderer, snakeTemp->r);

    while(snakeTemp->suivant != NULL)
    {
        snakeTemp->r->x = snakeTemp->suivant->r->x;
        snakeTemp->r->y = snakeTemp->suivant->r->y;
        snakeTemp = snakeTemp->suivant;
    }
    /* snakeTemp correspond à la tête du serpent */

    SDL_DestroyTexture(snakeTemp->img);
    switch(snake->direction)
    {
        case HAUT:
            snakeTemp->r->y -= snakeTemp->r->h;
            snakeTemp->img = IMG_LoadTexture(renderer, IMG_TETEH_PATH);
            break;
        case DROITE:
            snakeTemp->r->x += snakeTemp->r->w;
            snakeTemp->img = IMG_LoadTexture(renderer, IMG_TETED_PATH);
            break;
        case BAS:
            snakeTemp->r->y += snakeTemp->r->h;
            snakeTemp->img = IMG_LoadTexture(renderer, IMG_TETEB_PATH);
            break;
        case GAUCHE:
            snakeTemp->r->x -= snakeTemp->r->w;
            snakeTemp->img = IMG_LoadTexture(renderer, IMG_TETEG_PATH);
            break;
    }
    if(collisionPoint(snake, points)) { ajouterSerpent(snake, renderer); }

}

void ajouterSerpent(Snake *snake, SDL_Renderer *renderer)
{
    ElemSnake *nouveau = NULL;

    if((nouveau = (ElemSnake*)malloc(sizeof(ElemSnake))) == NULL)
        snakeERROR("Erreur allocation mémoire !");
    if((nouveau->r = (SDL_Rect*)malloc(sizeof(SDL_Rect))) == NULL)
        snakeERROR("Erreur allocation mémoire !");

    nouveau->img = IMG_LoadTexture(renderer, IMG_ROND_PATH);
    SDL_QueryTexture(nouveau->img, NULL, NULL, &nouveau->r->w, &nouveau->r->h);

    nouveau->suivant = snake->premier;
    snake->premier = nouveau;
    snake->nb++;

}

void libererSerpent(Snake *snake)
{
    ElemSnake *actuel = NULL;

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

int collisionPoint(Snake *s, Points *p)
{
    ElemSnake *snakeTete = s->premier;
    ElemPoint *pointemp  = p->premier;
    ElemPoint *pointprec = NULL;
    int collision = 0;

    /* Aller à la fin du serpent pour y trouver la tête */
    while(snakeTete->suivant != NULL)
        snakeTete = snakeTete->suivant;

    while(pointemp != NULL && collision == 0)
    {
        if(SDL_HasIntersection(snakeTete->r, pointemp->r))
        {
            collision = 1;
            if(pointprec == NULL)
                p->premier = pointemp->suivant; /* Il faut enlever le 1er élément */
            else
                pointprec->suivant = pointemp->suivant;

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
