#ifndef JATEKMENET_H_INCLUDED
#define JATEKMENET_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

/* mezok, ugyan olyan sorrendben mint a képen,
igy a kapott egesz szamok megegyeznek a png-beli indexekkel */
typedef enum Mezo{
    fedett, fedetlen, zaszlos, egy, ketto, harom , negy, ot, hat, het, nyolc, bomba, bombapiros
}Mezo;

/* a mezok.png faljben levo mezok merete */
enum { MERET = 20};

typedef struct cella
{
    int x;
    int y;
    bool b;
    Mezo milyen;
    bool zaszlos;
    bool latogatott;
}cella;

typedef enum Smiley{
    alap, nyer, veszit
}Smiley;

enum{ MERET2 = 30};

#endif // JATEKMENET_H_INCLUDED
