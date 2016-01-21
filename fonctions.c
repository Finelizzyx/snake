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
