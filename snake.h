#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

#define WIDTH 800
#define HEIGHT 600
#define DROITE 0
#define GAUCHE 1
#define BAS 2
#define HAUT 3
#define IMG_ROND_PATH "data/rond.png"
#define IMG_POINT_PATH "data/point.png"
#define NIVEAU1_PATH "data/niveau1.dat"

#ifdef MAINFILE
#define EXTERN
#else
#define EXTERN extern
#endif

typedef struct Snake
{
    SDL_Texture *img;
    SDL_Rect *r;
    struct Snake *suivant;

} Snake;

typedef struct Snakehead
{
    int nb;
    struct Snake *premier;
} Snakehead;

typedef struct Point
{
    SDL_Texture *img;
    SDL_Rect *r;
    struct Point *suivant;

} Point;

typedef struct Points
{
    int n; /* Nombre d'éléments */
    struct Point *premier;
} Points;

EXTERN SDL_Window *win;
EXTERN SDL_Renderer *renderer;
EXTERN SDL_Texture *img;
EXTERN int direction;
EXTERN int c;
EXTERN long vitesse;
EXTERN int continuer;
EXTERN Snakehead *snake;
EXTERN Points *points;


void afficherImage(SDL_Renderer *renderer, SDL_Texture *img, SDL_Rect *r);
void afficherSerpent(SDL_Renderer *renderer, Snakehead *snake);
Points *AfficherPoints(SDL_Renderer *renderer, const char *chemin);

Snakehead *initSerpent(SDL_Renderer *ecran);
void Serpent(Snakehead *snake, int dir);
void ajouterSerpent(Snakehead *snake, SDL_Renderer *ecran);
void libererSerpent(Snakehead *snake);

int collisionPoint(Snakehead *s, Points *p);

void snakeERROR(const char *erreur);

#endif
