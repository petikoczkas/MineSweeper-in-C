#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "timer.h"
#include "deklaraciok.h"

/* felhasznalhato zaszlok szama */
void zaszlosz(SDL_Renderer *renderer,  SDL_Surface *felirat, SDL_Texture *felirat_t, TTF_Font *font, SDL_Rect hova, int zaszlodb, int numx, int numy)
{
    SDL_Color piros={255,0,0};
    boxRGBA(renderer,20,0,60,59, 195, 195, 195,255);
    char a[12];
    if(zaszlodb<10 && zaszlodb>=0) sprintf(a, "0%d", zaszlodb);
    else sprintf(a, "%d", zaszlodb);
    felirat = TTF_RenderUTF8_Blended(font, a, piros);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    hova.x = (25);
    hova.y = 16;
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
    SDL_RenderPresent(renderer);
}
/* kiirja az eltelt idot */
void timer(SDL_Renderer *renderer,  SDL_Surface *felirat, SDL_Texture *felirat_t, TTF_Font *font, SDL_Rect hova, int sec, int numx, int numy)
{
    SDL_Color piros={255,0,0};
    char a[12];
    boxRGBA(renderer ,(numx*MERET)/2+30,0,numx*MERET,59, 195, 195, 195,255);
    if(sec<10) sprintf(a, "00%d", sec);
    else if(sec<100 && sec>9) sprintf(a, "0%d", sec);
    else sprintf(a, "%d", sec);
    felirat = TTF_RenderUTF8_Blended(font, a, piros);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    hova.x = (numx*MERET - felirat->w);
    hova.y = 16;
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
    SDL_RenderPresent(renderer);
}
/* meri az eltelt idot */
Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}
