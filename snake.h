#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#define WIDTH 800
#define HEIGHT 600
#define HAUT 3
#define BAS 2
#define DROITE 0
#define GAUCHE 1
#define IMG_PATH "data/rond.png"

typedef struct Snake
{
    SDL_Texture *img;
    SDL_Rect *r;
    struct Snake *suivant;

} Snake;

void afficherImage(SDL_Renderer *renderer, SDL_Texture *img, SDL_Rect *r);
void afficherSerpent(SDL_Renderer *renderer, Snake *snake);

#endif
