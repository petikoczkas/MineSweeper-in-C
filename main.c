#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#include "debugmalloc.h"
#include "timer.h"
#include "deklaraciok.h"
#include "jatekmenet.h"

int main(int argc, char *argv[]) {

    SDL_Window *window;
    SDL_Renderer *renderer;
    /* felirat megrajzolasa */
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    SDL_Rect hova = { 0, 0, 0, 0 };
    /* nehezsegi szint valasztasa */
    char nehezseg[9];
    printf("Valasszon nehezsegi szintet(Konnyu/Kozepes/Nehez): ");
    scanf("%s", nehezseg);
    while(strcmp(nehezseg, "Konnyu")!=0 && strcmp(nehezseg, "Kozepes")!=0 && strcmp(nehezseg, "Nehez")!=0)
    {
        printf("A feltuntetett lehetosegek kozul valasszon!\n");
        scanf("%s", nehezseg);
    }
    /* mezok szama, bombak szama , smiley koordinatai*/
    int numx, numy, bombasz, smileyx, smileyy=15;
    /* ablak létrehozása nehezsegi szinttol fuggoen*/
    int x1, y1, x2, y2;
    if(strcmp(nehezseg, "Konnyu")==0)
    {
        numx=9;
        numy=9;
        bombasz=10;
        smileyx=85;
        sdl_init("MineSweeper",200, 250, &window, &renderer);
        /* hatter */
        x1 = 0;
        y1 = 0;
        x2 =200;
        y2 =250;
        boxRGBA(renderer, x1, y1, x2, y2, 255, 255, 255, 255);
        /* fejlec */
        x1 = 10;
        y1 = 0;
        x2 =190;
        y2 =60;
        boxRGBA(renderer, x1, y1, x2, y2, 195, 195, 195, 255);
    }
    else if(strcmp(nehezseg, "Kozepes")==0)
    {
        numx=16;
        numy=16;
        bombasz=40;
        smileyx=155;
        sdl_init("MineSweeper", 340, 390, &window, &renderer);
        /* hatter */
        x1 = 0;
        y1 = 0;
        x2 =340;
        y2 =390;
        boxRGBA(renderer, x1, y1, x2, y2, 255, 255, 255, 255);
        /* fejlec */
        x1 = 10;
        y1 = 0;
        x2 =330;
        y2 =60;
        boxRGBA(renderer, x1, y1, x2, y2, 195, 195, 195, 255);
    }
    else if(strcmp(nehezseg, "Nehez")==0)
    {
        numx=30;
        numy=16;
        bombasz=99;
        smileyx=295;
        sdl_init("MineSweeper", 620, 390, &window, &renderer);
        /* hatter */
        x1 = 0;
        y1 = 0;
        x2 =620;
        y2 =390;
        boxRGBA(renderer, x1, y1, x2, y2, 255, 255, 255, 255);
        /* fejlec */
        x1 = 10;
        y1 = 0;
        x2 =610;
        y2 =60;
        boxRGBA(renderer, x1, y1, x2, y2, 195, 195, 195, 255);
    }
    SDL_RenderPresent(renderer);

     /* kep beolvasasa */
    SDL_Texture *mezo = IMG_LoadTexture(renderer, "mezok.png");
    if (mezo == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }
    /* smiley kep beolvasasa */
    SDL_Texture *smiley = IMG_LoadTexture(renderer, "smiley.png");
    if (smiley == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }

    /* betutipus betoltese, 28 pont magassaggal */
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("LiberationSerif-Regular.ttf", 28);
    if (!font) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }

    /* ket dimenzios tomb letrehozasa, memoriaterulet foglalasa */
    cella **m;
    foglalas(&m, numx+2, numy+2);

    alaphelyzet(renderer, mezo, fedett, m, numx, numy);

    bombak_helye(m, numx, numy, bombasz);

    generalas(renderer, mezo, m, numx, numy);

    smiley_kirajzol(renderer, smiley, alap, smileyx, smileyy);
    SDL_RenderPresent(renderer);
    /* idozito hozzaadasa */
    SDL_AddTimer(1000, idozit, NULL);

    int sec=0;
    int zaszlodb=bombasz;
    timer(renderer, felirat, felirat_t, font, hova, sec, numx, numy);
    zaszlosz(renderer, felirat, felirat_t, font, hova, zaszlodb, numx, numy);
    bool quit=false;
    bool click=false;
    bool vege=false;
    while(!quit)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_USEREVENT:
                if(click && !vege){
                    sec++;
                    timer(renderer, felirat, felirat_t, font, hova, sec, numx, numy);
                }
                break;
            case SDL_QUIT:
                quit=true;
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONUP:
                click=true;
                /* alaphelyzet visszaallitasa */
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(smileyx<event.button.x && event.button.x-smileyx<30)
                    {
                        if(smileyy<event.button.y && event.button.y-smileyy<30)
                        {
                            smiley_kirajzol(renderer, smiley, alap, smileyx, smileyy);
                            alaphelyzet(renderer, mezo, fedett, m, numx, numy);
                            bombak_helye(m, numx, numy, bombasz);
                            generalas(renderer, mezo, m, numx, numy);
                            zaszlodb=bombasz;
                            zaszlosz(renderer, felirat, felirat_t, font, hova, zaszlodb, numx, numy);
                            sec=0;
                            timer(renderer, felirat, felirat_t, font, hova, sec, numx, numy);
                            vege=false;
                            click=false;
                            SDL_RenderPresent(renderer);
                        }
                    }
                    /* a kattintas helye alapjan a mezo kiszamitasa amire rakattintottak */
                    for(int i=1; i<=numy; i++)
                    {
                        for(int j=1; j<=numx; j++)
                        {
                            if(m[i][j].x<event.button.x && event.button.x-m[i][j].x<20)
                            {
                                if(m[i][j].y<event.button.y && event.button.y-m[i][j].y<20)
                                {
                                    /* megfelelo mezo kirajzolasa */
                                    if(!(m[i][j].zaszlos))
                                    {
                                        if(m[i][j].milyen==fedetlen) kitolt(renderer, mezo, m, j, i, numx, numy);
                                        else if(m[i][j].b)
                                        {
                                            smiley_kirajzol(renderer, smiley, veszit, smileyx, smileyy);
                                            jatek_vege(renderer, mezo, m, j, i, numx, numy);
                                            vege=true;

                                        }
                                        else{
                                            mezo_kirajzol(renderer, mezo, m[i][j].milyen, m[i][j].x, m[i][j].y);
                                            m[i][j].latogatott=true;
                                        }
                                    }
                                    /* az elvegzett rajzolasok a kepernyore*/
                                    SDL_RenderPresent(renderer);
                                    if(nyert(renderer, smiley, m, numx, numy, smileyx, smileyy, bombasz)){
                                        vege=true;
                                        int time;
                                        FILE *fr;
                                        if(strcmp(nehezseg, "Konnyu")==0 || strcmp(nehezseg, "Kozepes")==0 || strcmp(nehezseg, "Nehez")==0) strcat(nehezseg, ".txt");                                        fr = fopen(nehezseg, "r");
                                        if(fr!=NULL){
                                            fscanf(fr, "%d", &time);
                                            fclose(fr);
                                        }
                                        else perror("Nem sikerult megnyitni a fajlt");
                                        FILE *fw;
                                        fw = fopen(nehezseg, "w");
                                        if(fw!=NULL){
                                            if(time==0){
                                                fprintf(fw, "%d", sec);
                                                printf("Legjobb ido: %dmp\nMostani ido: %dmp\n", sec, sec);
                                            }
                                            else if(time>sec){
                                                fprintf(fw, "%d", sec);
                                                printf("Elozo legjobb ido: %dmp\nUj legjobb ido: %dmp\n", time, sec);
                                            }
                                            else printf("Legjobb ido: %dmp\nMostani ido: %dmp\n", time, sec);
                                            printf("\n");
                                            fclose(fw);
                                        }
                                        else perror("Nem sikerult megnyitni a fajlt");
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                if(event.button.button == SDL_BUTTON_RIGHT){
                    /* a kattintas helye alapjan a mezo kiszamitasa amire rakattintottak */
                    for(int i=1; i<=numy; i++)
                    {
                        for(int j=1; j<=numx; j++)
                        {
                            if(m[i][j].x<event.button.x && event.button.x-m[i][j].x<20)
                            {
                                if(m[i][j].y<event.button.y && event.button.y-m[i][j].y<20)
                                {
                                    /* megfelelo mezo kirajzolasa */
                                    if(!(m[i][j].zaszlos) &&  !m[i][j].latogatott)
                                    {
                                        mezo_kirajzol(renderer, mezo, zaszlos, m[i][j].x, m[i][j].y);
                                        m[i][j].zaszlos=true;
                                        zaszlodb--;
                                        zaszlosz(renderer, felirat, felirat_t, font, hova, zaszlodb, numx, numy);

                                    }
                                    else if(m[i][j].zaszlos)
                                    {
                                        mezo_kirajzol(renderer, mezo, fedett, m[i][j].x, m[i][j].y);
                                        m[i][j].zaszlos=false;
                                        zaszlodb++;
                                        zaszlosz(renderer, felirat, felirat_t, font, hova, zaszlodb, numx, numy);

                                    }
                                    /* az elvegzett rajzolasok a kepernyore*/
                                    SDL_RenderPresent(renderer);
                                }
                            }
                        }
                    }
                    break;
                }
        }
    }
    /*memoriaterulet felszabaditasa*/
    SDL_DestroyTexture(mezo);
    SDL_DestroyTexture(smiley);
    TTF_CloseFont(font);
    felszabadit(m, numy+2);
    return 0;
}
