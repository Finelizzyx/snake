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
#define MAX_NIVEAUX 2
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
    int nb; /* Nombre d'éléments */
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
EXTERN SDL_bool continuer;
EXTERN Snake *snake;
EXTERN Points *points;
EXTERN int tempsActuel;
EXTERN int tempsPrecedent;
EXTERN int niveauActuel;


void afficherImage(SDL_Renderer *renderer, SDL_Texture *img, SDL_Rect *r);
void afficherSerpent(SDL_Renderer *renderer, Snake *snake);
void afficherPoints(SDL_Renderer *renderer, Points *points);
/*Points* AfficherPointsBis(SDL_Renderer *renderer, const char *chemin);*/

Snake* initSerpent(SDL_Renderer *renderer);
void deplacerSerpent(Snake *snake, SDL_Renderer *renderer);
void ajouterSerpent(Snake *snake, SDL_Renderer *renderer);
void libererSerpent(Snake *snake);

Points* initPoints(void);
void chargerPoints(Points *points, int niveau);
void ajouterPoint(Points *points, SDL_Renderer *renderer, int x, int y);
void supprimerPoint(Points *points, ElemPoint *elemASupprimer);
SDL_bool pointsVide(Points *points);
void libererPoints(Points *points);
void chargerNiveau(char* chaine, int niveau);

SDL_bool collisionPoint(Snake *snake, Points *points);
SDL_bool collisionSerpent(Snake *snake);

void snakeERROR(const char *erreur);

#endif
