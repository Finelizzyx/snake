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

void afficherSerpent(SDL_Renderer *renderer, Snakehead *snake)
{
    Snake *snakeTemp = snake->premier;

    while(snakeTemp != NULL) /* Affichage du corps */
    {
        afficherImage(renderer, snakeTemp->img, snakeTemp->r);
        snakeTemp = snakeTemp->suivant;
    }
}

Points *AfficherPoints(SDL_Renderer *renderer, const char *chemin)
{
    FILE *f;
    Points *pts;
    Point *p = NULL;
    Point *pre = NULL; /* Point précédent pour lagestion du suivant */
    SDL_Rect *rect;
    int x, y;
    int c = 0; /* Nombre d'éléments */

    pts = (Points*)malloc(sizeof(Points));
    pts->premier = NULL;

    if((f = fopen(chemin, "r")) != NULL)
    {
        while((fscanf(f, "%d,%d", &x, &y)) != EOF)
        {
            p = (Point*)malloc(sizeof(Point));
            p->img = IMG_LoadTexture(renderer, IMG_POINT_PATH);
            rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
            rect->x = x * 25; rect->y = y * 25;
            rect->h = h; rect->w = w;
            p->r = rect;
            p->suivant = NULL;
            afficherImage(renderer, p->img, p->r);
            if(pts->premier == NULL) { pts->premier = p; }
            else {
                if(pre != NULL) {
                    pre->suivant = p;
                }
                pre = p;
            }
            c++;
        }
    }
    fclose(f);

    pts->n = c;

    return pts;
}

