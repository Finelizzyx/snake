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
    Point *pre = NULL; /* Point précédent pour la gestion du suivant */
    SDL_Rect *rect;
    int x, y;
    int c = 0; /* Nombre d'éléments */
    char cerreur[128];

    pts = (Points*)malloc(sizeof(Points));
    pts->premier = NULL;

    if((f = fopen(chemin, "r")) != NULL)
    {
        while((fscanf(f, "%d,%d", &x, &y)) != EOF)
        {
            p = (Point*)malloc(sizeof(Point));
            rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
            p->img = IMG_LoadTexture(renderer, IMG_POINT_PATH);
            SDL_QueryTexture(p->img, NULL, NULL, &rect->w, &rect->h);
            rect->x = x * rect->w;
            rect->y = y * rect->h;
            p->r = rect;
            p->suivant = NULL;
            afficherImage(renderer, p->img, p->r);
            if(pts->premier == NULL) {
                pts->premier = p;
                pre = p;
            }
            else {
                if(pre != NULL) {
                    pre->suivant = p;
                }
                pre = p;
            }
            c++;
        }
    }
    else
    {
        sprintf(cerreur, "Impossible d'ouvrir le fichier %s !", chemin);
        snakeERROR(cerreur);
    }
    fclose(f);

    pts->n = c;

    return pts;
}

