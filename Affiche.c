/* ##################
Affiche.c
Fonctions d'affichage du serpent
##################### */

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "snake.h"

void afficherImage(SDL_Renderer *renderer, SDL_Texture *img, SDL_Rect *r)
{
    SDL_RenderCopy(renderer, img, NULL, r);
    SDL_RenderPresent(renderer);
}

void afficherSerpent(SDL_Renderer *renderer, Snake *snake)
{
    ElemSnake *snakeTemp = snake->premier;

    while(snakeTemp != NULL) /* Affichage du corps */
    {
        afficherImage(renderer, snakeTemp->img, snakeTemp->r);
        snakeTemp = snakeTemp->suivant;
    }
}

void afficherPoints(SDL_Renderer *renderer, Points *points)
{
    ElemPoint *pointTemp = points->premier;

    while(pointTemp != NULL)
    {
        afficherImage(renderer, pointTemp->img, pointTemp->r);
        pointTemp = pointTemp->suivant;
    }
}
