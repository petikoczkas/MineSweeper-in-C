#include "deklaraciok.h"
#include "jatekmenet.h"

/* kulon fuggvenybe, hogy olvashatobb legyen */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

/* megfelelo kep megejelnitese */
void mezo_kirajzol(SDL_Renderer *renderer, SDL_Texture *mezo, Mezo melyik, int x, int y)
{
    SDL_Rect forras = {(melyik% 13)*20, 0, MERET, MERET};
    SDL_Rect cel = {x, y, MERET, MERET};
    SDL_RenderCopy(renderer, mezo, &forras, &cel);
}



void smiley_kirajzol(SDL_Renderer *renderer, SDL_Texture *smiley, Smiley melyik, int x, int y)
{
    SDL_Rect forras = {melyik*MERET2, 0, MERET2, MERET2};
    SDL_Rect cel = {x, y, MERET2, MERET2};
    SDL_RenderCopy(renderer, smiley, &forras, &cel);
}

/* memoriaterulet lefoglalasa
    fel kell szabaditani!*/
void foglalas(cella ***uj, int numx, int numy)
{
    cella **m;
    m=(cella**) malloc(numy*sizeof(cella*));
    for(int i=0; i<numy; i++) m[i]=(cella*) malloc(numx*sizeof(cella));
    *uj=m;
}

/* memoriaterulet felszabaditasa */
void felszabadit(cella **m, int numy)
{
    for(int i=0; i<numy; i++) free(m[i]);
    free(m);
}

/* alaphelyzet kirajzolasa (lefedett mezok) */
void alaphelyzet(SDL_Renderer *renderer, SDL_Texture *mezo, Mezo melyik, cella **m, int numx, int numy)
{
    int x=1, y=1;
    for(int i=60; i<numy*20+60; i+=20)
    {
        y=1;
        for(int j=10; j<numx*20; j+=20)
        {
            m[x][y].x=j;
            m[x][y].y=i;
            m[x][y].b=false;
            m[x][y].zaszlos=false;
            m[x][y].latogatott=false;
            mezo_kirajzol(renderer, mezo, melyik, j, i);
            y++;
        }
        x++;
    }
}

/* bombak helyenek kisorsolasa */
void bombak_helye(cella **m, int numx, int numy, int bombasz)
{
    int b[bombasz];
    srand(time(0));
    for(int i=0; i<bombasz; i++)
    {
        bool egyezes=true;
        while(egyezes){
            b[i]=rand()%(numx*numy-1);
            egyezes=false;
        for(int j=0; j<i; j++)
        {
            if(b[j]==b[i])
                egyezes=true;
        }
        }
    }
    /* bombak helyenek megjelolese */
    for(int i=0; i<bombasz; i++) m[b[i]/numx+1][b[i]%numx+1].b=true;
}

/* bombak es szamok helyenek meghatarozasa */
void generalas(SDL_Renderer *renderer, SDL_Texture *mezo, cella **m, int numx, int numy)
{
    int x=1, y=1, db=0;
    for(int i=60; i<numy*20+60; i+=20)
    {
        y=1;
        for(int j=10; j<numx*20; j+=20)
        {
            m[x][y].x=j;
            m[x][y].y=i;
            if(m[x][y].b) m[x][y].milyen=bomba;
            else
            {
                if(m[x-1][y].b) db++;
                if(m[x-1][y-1].b) db++;
                if(m[x][y-1].b) db++;
                if(m[x+1][y-1].b) db++;
                if(m[x+1][y].b) db++;
                if(m[x+1][y+1].b) db++;
                if(m[x][y+1].b) db++;
                if(m[x-1][y+1].b) db++;
                switch(db)
                {
                    case 0: m[x][y].milyen=fedetlen; break;
                    case 1: m[x][y].milyen=egy; break;
                    case 2: m[x][y].milyen=ketto; break;
                    case 3: m[x][y].milyen=harom; break;
                    case 4: m[x][y].milyen=negy; break;
                    case 5: m[x][y].milyen=ot; break;
                    case 6: m[x][y].milyen=hat;  break;
                    case 7: m[x][y].milyen=het; break;
                    case 8: m[x][y].milyen=nyolc; break;
                    default: m[x][y].milyen=fedetlen; break;
                }
            }
            y++;
            db=0;
        }
        x++;
    }
}


/* az ures mezok mezok felfedese rekurziv lepessel */
void kitolt(SDL_Renderer *renderer, SDL_Texture *mezo, cella **m, int j, int i, int numx, int numy)
{
    if(i<1 || j<1 || i>numy || j>numx) return;
    if(m[i][j].latogatott) return;
    if(m[i][j].milyen==bomba) return;
    if(m[i][j].zaszlos) return;
    m[i][j].latogatott=true;
    if(m[i][j].milyen!=fedetlen && !(m[i][j].zaszlos))
    {
        mezo_kirajzol(renderer, mezo, m[i][j].milyen, m[i][j].x, m[i][j].y);
        SDL_RenderPresent(renderer);
        return;
    }
    mezo_kirajzol(renderer, mezo, m[i][j].milyen, m[i][j].x, m[i][j].y);
    SDL_RenderPresent(renderer);
    int dj[8]={1,-1,0, 0,1,-1, 1,-1};
    int di[8]={0, 0,1,-1,1, 1,-1,-1};
    for(int k=0; k<8; k++) kitolt(renderer, mezo, m, j+dj[k], i+di[k], numx, numy);
}
/* felfedi az osszes mezot es amelyik bombara kattintottunk az piros lesz */
void jatek_vege(SDL_Renderer *renderer, SDL_Texture *mezo, cella **m, int j, int i, int numx, int numy)
{
    for(int k=1; k<=numy; k++)
    {
        for(int l=1; l<=numx; l++)
        {
            mezo_kirajzol(renderer, mezo, m[k][l].milyen,  m[k][l].x, m[k][l].y);
        }
    }
    mezo_kirajzol(renderer, mezo, bombapiros, m[i][j].x, m[i][j].y);
    SDL_RenderPresent(renderer);
}
/* igazzal ter vissza ha csak a bombak felfedetlenek */
bool nyert(SDL_Renderer *renderer, SDL_Texture *smiley, cella **m, int numx, int numy, int smileyx, int smileyy, int bombasz)
{
    int db=0;
    for(int y=1; y<=numy; y++)
    {
        for(int x=1; x<=numx; x++)
        {
            if(m[y][x].latogatott==false) db++;
        }
    }
    if(db==bombasz){
        smiley_kirajzol(renderer, smiley, nyer, smileyx, smileyy);
        SDL_RenderPresent(renderer);
        return true;
    }
    return false;
}
