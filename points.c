/** #########################################
Gestion des points
############################################
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

#include "snake.h"

Points* initPoints(void)
{
    Points *points = NULL;

    if((points = (Points*)malloc(sizeof(Points))) == NULL)
        snakeERROR("Erreur allocation mémoire");

    points->nb = 0;
    points->premier = NULL;

    return points;
}

void chargerPoints(Points *points, int niveau)
{
    FILE *f;
    int x, y;
    char chemin[20] = "";

    sprintf(chemin, "data/niveau%d.dat", niveau);

    if((f = fopen(chemin, "r")) != NULL)
        while((fscanf(f, "%d,%d", &x, &y)) != EOF)
            ajouterPoint(points, renderer, x, y);
    else
        snakeERROR("Impossible d'ouvrir le fichier %s !", chemin);

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

    if(!pointsVide(points))
    {
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
}

SDL_bool pointsVide(Points *points)
{
    return points->premier == NULL;
}

void libererPoints(Points *points)
{
    ElemPoint *actuel = NULL;

    while(!pointsVide(points))
    {
        actuel = points->premier;
        points->premier = points->premier->suivant;
        SDL_DestroyTexture(actuel->img);
        free(actuel->r);
        free(actuel);
    }
    free(points);
}
