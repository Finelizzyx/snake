/* #########################################
Fonctions diverses
############################################ */
#include <stdlib.h>
#include <stdio.h>

#include "snake.h"

void snakeERROR(const char *erreur)
{
    fprintf(stderr, "ERROR - %s\n", erreur);
    exit(EXIT_FAILURE);
}

void afficherTexte(SDL_Renderer *renderer)
{
    ;
}

void terminer(SDL_bool gagner)
{
    if(gagner) /* On a gagné */
    {
        ;
    }
    else /* On a perdu */
    {
        ;
    }
}
