#include "AlgoritmoBresenham.h"

AlgoritmoBresenham::AlgoritmoBresenham(){}

AlgoritmoBresenham::~AlgoritmoBresenham(){}

void AlgoritmoBresenham::DesenhaLinha(int x1, int y1, int x2, int y2, Uint32 cor, SDL_Gerenciador sdl_Gerenciador) {
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const int dx = x2 - x1;
    const int dy = fabs(y2 - y1);

    int error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for(int x=(int)x1; x<=maxX; x++) {
        if(steep) {
            sdl_Gerenciador.setPixel(y, x, cor);
        } else {
            sdl_Gerenciador.setPixel(x, y, cor);
        }

        error -= dy;
        if(error < 0) {
            y += ystep;
            error += dx;
        }
    }
}



void AlgoritmoBresenham::EightWaySymmetricPlot(int xc,int yc,int x,int y,Uint32 color,SDL_Gerenciador sdl_Gerenciador)
{
    sdl_Gerenciador.setPixel(x+xc,y+yc,color);
    sdl_Gerenciador.setPixel(x+xc,-y+yc,color);
    sdl_Gerenciador.setPixel(-x+xc,-y+yc,color);
    sdl_Gerenciador.setPixel(-x+xc,y+yc,color);
    sdl_Gerenciador.setPixel(y+xc,x+yc,color);
    sdl_Gerenciador.setPixel(y+xc,-x+yc,color);
    sdl_Gerenciador.setPixel(-y+xc,-x+yc,color);
    sdl_Gerenciador.setPixel(-y+xc,x+yc,color);
}

void AlgoritmoBresenham::BresenhamCircle(int xc,int yc,int r,Uint32 color,SDL_Gerenciador sdl_Gerenciador)
{
    int x=0,y=r,d=3-(2*r);
    EightWaySymmetricPlot(xc,yc,x,y,color,sdl_Gerenciador);

    while(x<=y)
     {
      if(d<=0)
             {
        d=d+(4*x)+6;
      }
     else
      {
        d=d+(4*x)-(4*y)+10;
        y=y-1;
      }
       x=x+1;
       EightWaySymmetricPlot(xc,yc,x,y,color,sdl_Gerenciador);
      }

      PaintArea(xc,yc,color,sdl_Gerenciador);
}

//busca em profundidade, pinta tudo dentro do círculo
void AlgoritmoBresenham::PaintArea(int x,int y,Uint32 color,SDL_Gerenciador sdl_Gerenciador){

    int xGraphMovment[] = {1,0,-1,0};
    int ygraphMovment[] = {0,1,0,-1};

    pair<int,int> searchCenter (x,y);

    queue<pair<int,int>> queue_;
    queue_.push(searchCenter);

    while(!queue_.empty()){
        searchCenter = queue_.front();
        queue_.pop();

        for(int i=0;i<4;i++){
            //direção do pixel cima,baixo,esquerda e direita
            pair<int,int> newPoint (searchCenter.first+xGraphMovment[i],searchCenter.second+ygraphMovment[i]);

            if(sdl_Gerenciador.getPixel(newPoint.first,newPoint.second) != color){  //verifica borda do circulo
                sdl_Gerenciador.setPixel(newPoint.first,newPoint.second,color);
                queue_.push(newPoint);
            }
        }
    }
}

