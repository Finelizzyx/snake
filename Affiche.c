/** ##################
Affiche.c
Fonctions d'affichage du serpent
#####################
*/
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

void afficherTexte(SDL_Renderer *renderer, const char *texte, TTF_Font *police, int x, int y, int r, int g, int b)
{
    SDL_Surface *texteSurface = NULL;
    SDL_Texture *texteTexture = NULL;
    SDL_Rect rect;
    SDL_Color couleur;
    SDL_Color noir = {0, 0, 0, 255};

    /* couleur du texte */
    couleur.r = r;
    couleur.g = g;
    couleur.b = b;
    couleur.a = 255;

    if((texteSurface = TTF_RenderText_Shaded(police, texte, couleur, noir)) != NULL)
    {
        texteTexture = SDL_CreateTextureFromSurface(renderer, texteSurface);
        SDL_FreeSurface(texteSurface);
        texteSurface = NULL;

        rect.x = x;
        rect.y = y;

        SDL_QueryTexture(texteTexture, NULL, NULL, &rect.w, &rect.h);
        SDL_RenderCopy(renderer, texteTexture, NULL, &rect);

        SDL_DestroyTexture(texteTexture);
    }
    else
        snakeERROR("Le texte %s n'a pas pu être afficher : %s\n", texte, TTF_GetError());
}
