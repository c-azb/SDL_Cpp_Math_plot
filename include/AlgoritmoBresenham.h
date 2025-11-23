#ifndef ALGORITMOBRESENHAM_H
#define ALGORITMOBRESENHAM_H

#include "SDL_Gerenciador.h"
#include <math.h>
#include <queue>

using namespace std;

class AlgoritmoBresenham {

    public:
        AlgoritmoBresenham();
        static void DesenhaLinha(int x1, int y1, int x2, int y2, Uint32 cor,SDL_Gerenciador sdl_Gerenciador);
        static void BresenhamCircle(int xc,int yc,int r,Uint32 color,SDL_Gerenciador sdl_Gerenciador);

        virtual ~AlgoritmoBresenham();

    protected:

    private:
        static void PaintArea(int x,int y,Uint32 color,SDL_Gerenciador sdl_Gerenciador);
        static void EightWaySymmetricPlot(int xc,int yc,int x,int y,Uint32 color,SDL_Gerenciador sdl_Gerenciador);
};

#endif
