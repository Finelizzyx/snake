/** #########################################
Fonctions diverses
############################################
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "snake.h"

void init(void)
{
    atexit(quit);

    /* Initialisation de la SDL2 */
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        snakeERROR("Impossible d'initialiser SDL2 : %s\n", SDL_GetError());

    /* Initialisation de SDL_ttf */
    if(TTF_Init() < 0)
        snakeERROR("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
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

void snakeERROR(const char *erreur, ...)
{
    va_list ap; /* variable de gestion des paramètres variables */
    int i;
    char buffer[128] = {0}; /* Chaîne intermédiaire */

    va_start(ap, erreur); /* Pour initialiser la gestion des paramètres variables */

    fprintf(stderr, "ERROR - ");

    for(i = 0; i < strlen(erreur); i++)
    {
        if(erreur[i] == '%')
        {
            i++;
            switch(erreur[i])
            {
                case 'd': /* int */
                    sprintf(buffer, "%d", va_arg(ap, int));
                    fprintf(stderr, "%s", buffer);
                    break;
                case 'c': /* char */
                    fprintf(stderr, "%c", va_arg(ap, int));
                    break;
                case 's': /* char* */
                    fprintf(stderr, "%s", va_arg(ap, char*));
                    break;
                case '%':
                    fprintf(stderr, "%%");
                    break;
            }
        }
        else
            fprintf(stderr, "%c", erreur[i]);
    }
    fprintf(stderr, "\n");

    va_end(ap); /* Pour terminer la gestion des paramètres variables */
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
