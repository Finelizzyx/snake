#include <stdlib.h>
#include <stdio.h>

#include "snake.h"

void snakeERROR(const char *erreur)
{
    fprintf(stderr, erreur);
    exit(EXIT_FAILURE);
}