/* #########################################
Gestion du serpent
############################################ */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#include "snake.h"

Snake* initSerpent(SDL_Renderer *renderer)
{
    Snake *snake = NULL;
    ElemSnake *elemSnake = NULL;

    if((snake = (Snake*)malloc(sizeof(Snake))) == NULL)
        snakeERROR("Erreur allocation mémoire !");

    snake->nb = 1;
    snake->direction = rand()%4; /* Donne une direction aléatoire à l'initialisation */

    if((elemSnake = (ElemSnake*)malloc(sizeof(ElemSnake))) == NULL)
        snakeERROR("Erreur allocation mémoire !");

    if((elemSnake->r = (SDL_Rect*)malloc(sizeof(SDL_Rect))) == NULL)
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

void deplacerSerpent(Snake *snake, SDL_Renderer *renderer) /*Tête dans la bonne direction et glissement du reste du corps */
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
    if(collisionPoint(snake, points))
        ajouterSerpent(snake, renderer);

    if(collisionSerpent(snake))
        continuer = SDL_FALSE;

    /* Si le serpent sort de l'écran, il réapparaît de l'autre côté */
    if(snakeTemp->r->x >= WIDTH)
        snakeTemp->r->x = 0;
    if(snakeTemp->r->x < 0)
        snakeTemp->r->x = WIDTH - snakeTemp->r->w;
    if(snakeTemp->r->y >= HEIGHT)
        snakeTemp->r->y = 0;
    if(snakeTemp->r->y < 0)
        snakeTemp->r->y = HEIGHT - snakeTemp->r->h;
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

    nouveau->r->x = -50;
    nouveau->r->y = -50;

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

SDL_bool collisionPoint(Snake *snake, Points *points)
{
    ElemSnake *snakeTete = snake->premier;
    ElemPoint *pointTemp = points->premier;
    SDL_bool collision = SDL_FALSE;

    /* Aller à la fin du serpent pour y trouver la tête */
    while(snakeTete->suivant != NULL)
        snakeTete = snakeTete->suivant;

    /* snakeTete est le dernier élément donc la tête du serpent */
    while(pointTemp != NULL && !collision)
    {
        if(SDL_HasIntersection(snakeTete->r, pointTemp->r))
        {
            collision = SDL_TRUE;
            supprimerPoint(points, pointTemp);
        }
        else
            pointTemp = pointTemp->suivant;
    }

    return collision;
}

SDL_bool collisionSerpent(Snake *snake)
{
    ElemSnake *snakeTete = snake->premier;
    ElemSnake *actuel = snake->premier;
    SDL_bool collision = SDL_FALSE;

    while(snakeTete->suivant != NULL)
        snakeTete = snakeTete->suivant;

    /* snakeTete est le dernier élément donc la tête du serpent */
    while(actuel != snakeTete && !collision)
    {
        if(SDL_HasIntersection(actuel->r, snakeTete->r))
            collision = SDL_TRUE;

        actuel = actuel->suivant;
    }

    return collision;
}
