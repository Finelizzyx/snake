#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#define WIDTH 800
#define HEIGHT 600
#define HAUT 3
#define BAS 2
#define DROITE 0
#define GAUCHE 1
#define IMG_PATH "data/rond.png"

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

EXTERN SDL_Window *win;
EXTERN SDL_Renderer *renderer;
EXTERN SDL_Texture *img;
EXTERN int w, h; /* texture width & height */
EXTERN SDL_Rect texr;
EXTERN int direction;
EXTERN int c;
EXTERN int vitesse;
EXTERN int continuer;
EXTERN Snake *snake;


void afficherImage(SDL_Renderer *renderer, SDL_Texture *img, SDL_Rect *r);
void afficherSerpent(SDL_Renderer *renderer, Snake *snake);

#endif
