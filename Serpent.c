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

Points* initPoints(void)
{
    Points *points = NULL;

    if((points = (Points*)malloc(sizeof(Points))) == NULL)
        snakeERROR("Erreur allocation mémoire");

    points->nb = 0;
    points->premier = NULL;

    return points;
}

void chargerPoints(Points *points, const char *chemin)
{
    FILE *f;
    int x, y;
    char erreur[128];

    if((f = fopen(chemin, "r")) != NULL)
        while((fscanf(f, "%d,%d", &x, &y)) != EOF)
            ajouterPoint(points, renderer, x, y);
    else
    {
        sprintf(erreur, "Impossible d'ouvrir le fichier %s !", chemin);
        snakeERROR(erreur);
    }
    fclose(f);
}

void ajouterPoint(Points *points, SDL_Renderer *renderer, int x, int y)
{
    ElemPoint *nouveau = NULL;

    if((nouveau = (ElemPoint*)malloc(sizeof(ElemPoint))) == NULL)
        snakeERROR("Erreur allocation mémoire");
    if((nouveau->r = (SDL_Rect*)malloc(sizeof(SDL_Rect))) == NULL)
        snakeERROR("Erreur allocation mémoire !");

    nouveau->img = IMG_LoadTexture(renderer, IMG_POINT_PATH);
    SDL_QueryTexture(nouveau->img, NULL, NULL, &nouveau->r->w, &nouveau->r->h);
    nouveau->r->x = x * nouveau->r->w;
    nouveau->r->y = y * nouveau->r->h;

    nouveau->suivant = points->premier;
    points->premier = nouveau;
    points->nb++;
}

void supprimerPoint(Points *points, ElemPoint *elemASupprimer)
{
    ElemPoint *actuel = NULL;

    if(elemASupprimer == points->premier)
    {
        points->premier = points->premier->suivant;
        SDL_DestroyTexture(elemASupprimer->img);
        free(elemASupprimer->r);
        free(elemASupprimer);
    }
    else
    {
        actuel = points->premier;
        while(actuel->suivant != elemASupprimer)
            actuel = actuel->suivant;

        /* actuel est le précédent de l'élément à supprimer */
        if(actuel->suivant != NULL)
        {
            actuel->suivant = elemASupprimer->suivant;
            SDL_DestroyTexture(elemASupprimer->img);
            free(elemASupprimer->r);
            free(elemASupprimer);
        }
    }

}

void libererPoints(Points *points)
{
    ElemPoint *actuel = NULL;

    while(points->premier != NULL)
    {
        actuel = points->premier;
        points->premier = points->premier->suivant;
        SDL_DestroyTexture(actuel->img);
        free(actuel->r);
        free(actuel);
    }
    free(points);
}

SDL_bool collisionPoint(Snake *snake, Points *points)
{
    ElemSnake *snakeTete = snake->premier;
    ElemPoint *pointTemp = points->premier;
    int collision = SDL_FALSE;

    /* Aller à la fin du serpent pour y trouver la tête */
    while(snakeTete->suivant != NULL)
        snakeTete = snakeTete->suivant;

    /* snakeTete est le dernier élément càd la tête du serpent */
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
