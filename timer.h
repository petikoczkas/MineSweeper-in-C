#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

void zaszlosz(SDL_Renderer *renderer,  SDL_Surface *felirat, SDL_Texture *felirat_t, TTF_Font *font, SDL_Rect hova, int zaszlodb, int numx, int numy);

void timer(SDL_Renderer *renderer,  SDL_Surface *felirat, SDL_Texture *felirat_t, TTF_Font *font, SDL_Rect hova, int sec, int numx, int numy);

Uint32 idozit(Uint32 ms, void *param);

#endif // TIMER_H_INCLUDED
