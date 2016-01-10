/* ##################
Affiche.c
Fonctions d'affichage du serpent
##################### */

#include <SDL.h>
#include <SDL_image.h>

#include "snake.h"

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

