#ifndef JATEKMENET_H_INCLUDED
#define JATEKMENET_H_INCLUDED

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);

void mezo_kirajzol(SDL_Renderer *renderer, SDL_Texture *mezo, Mezo melyik, int x, int y);

void smiley_kirajzol(SDL_Renderer *renderer, SDL_Texture *smiley, Smiley melyik, int x, int y);

void foglalas(cella ***uj, int numx, int numy);

void felszabadit(cella **m, int numy);

void alaphelyzet(SDL_Renderer *renderer, SDL_Texture *mezo, Mezo melyik, cella **m, int numx, int numy);

void bombak_helye(cella **m, int numx, int numy, int bombasz);

void generalas(SDL_Renderer *renderer, SDL_Texture *mezo, cella **m, int numx, int numy);

void kitolt(SDL_Renderer *renderer, SDL_Texture *mezo, cella **m, int j, int i, int numx, int numy);

void jatek_vege(SDL_Renderer *renderer, SDL_Texture *mezo, cella **m, int j, int i, int numx, int numy);

bool nyert(SDL_Renderer *renderer, SDL_Texture *smiley, cella **m, int numx, int numy, int smileyx, int smileyy, int bombasz)

#endif // JATEKMENET_H_INCLUDED
