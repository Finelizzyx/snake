#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

#define WIDTH 800
#define HEIGHT 600
#define IMG_TETEH_PATH "data/teteh.png"
#define IMG_TETED_PATH "data/teted.png"
#define IMG_TETEB_PATH "data/teteb.png"
#define IMG_TETEG_PATH "data/teteg.png"
#define IMG_ROND_PATH "data/rond.png"
#define IMG_POINT_PATH "data/point.png"
#define NIVEAU1_PATH "data/niveau1.dat"
#define INTERVALLE 200

#ifdef MAINFILE
#define EXTERN
#else
#define EXTERN extern
#endif

typedef enum Direction
{
    HAUT, DROITE, BAS, GAUCHE

} Direction;

typedef struct ElemSnake /* Eléments de la liste du snake*/
{
    SDL_Texture *img;
    SDL_Rect *r;
    struct ElemSnake *suivant;

} ElemSnake;

typedef struct Snake /* Structure de contrôle gérant le snake */
{
    int nb; /* Noombre d'éléments */
    Direction direction; /* Direction du serpent */
    ElemSnake *premier;
} Snake;

typedef struct ElemPoint /* Elément de la liste de points */
{
    SDL_Texture *img;
    SDL_Rect *r;
    struct ElemPoint *suivant;

} ElemPoint;

typedef struct Points /* Structure de contrôle gérant les points */
{
    int nb; /* Nombre d'éléments */
    ElemPoint *premier;

} Points;

EXTERN SDL_Window *win;
EXTERN SDL_Renderer *renderer;
EXTERN int continuer;
EXTERN Snake *snake;
EXTERN Points *points;
EXTERN int tempsActuel;
EXTERN int tempsPrecedent;


void afficherImage(SDL_Renderer *renderer, SDL_Texture *img, SDL_Rect *r);
void afficherSerpent(SDL_Renderer *renderer, Snake *snake);
Points* AfficherPoints(SDL_Renderer *renderer, const char *chemin);

Snake* initSerpent(SDL_Renderer *renderer);
void deplacerSerpent(Snake *snake);
void ajouterSerpent(Snake *snake, SDL_Renderer *ecran);
void libererSerpent(Snake *snake);

Points* initPoints(SDL_Renderer *renderer);
void ajouterPoint(Points *points, SDL_Renderer *renderer, int x, int y);
void supprimerPoint(Points *points, ElemPoint *elemASupprimer);
void libererPoints(Points *points);

int collisionPoint(Snake *s, Points *p);

void snakeERROR(const char *erreur);

#endif
