/** #########################################
Fonctions diverses
############################################
*/
#include <stdlib.h>
#include <stdio.h>

#include "snake.h"

void init(void)
{
    char erreur[128];

    atexit(quit);

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        sprintf(erreur, "Impossible d'initialiser SDL2 : %s\n", SDL_GetError());
        snakeERROR(erreur);
    }

    /* Initialisation de SDL_ttf */
    if(TTF_Init() < 0)
    {
        sprintf(erreur, "Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        snakeERROR(erreur);
    }
}

void quit(void)
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
    libererSerpent(snake);
    libererPoints(points);
    TTF_CloseFont(police);

    TTF_Quit();
    SDL_Quit();
}

void snakeERROR(const char *erreur)
{
    fprintf(stderr, "ERROR - %s\n", erreur);
    exit(EXIT_FAILURE);
}

void terminer(SDL_bool gagner)
{
    if(gagner) /* On a gagné */
    {
        afficherTexte(renderer, "Gagné !", police, 400, 300, 255, 255, 255);
    }
    else /* On a perdu */
    {
        afficherTexte(renderer, "Perdu !", police, 400, 300, 255, 255, 255);
    }
}
