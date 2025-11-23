#include "Graficos.h"

#define EQUACAO1(x) x
#define EQUACAO2(x) -x
#define EQUACAO3(x) 2*x*x-6*x+1
#define EQUACAO4(x) sin(x)
#define EQUACAO5(x) -(x*x)+4

#define COUNT_EQUACAO 5
#define TAMANHO_DIV 5


Graficos::Graficos(pair<int,int> centro, int xSizeSet, int ySizeSet, int minXSet, int maxXset, int teclaMais, int teclaMenos)
{
    centroGrafico = origemGrafico = centro;

    xSize = xSizeSet;
    ySize = ySizeSet;

    minX = minY = minXSet;
    maxX = maxY = maxXset;

    clicaMais = teclaMais;
    clicaMenos = teclaMenos;

    SetaOrigem();
}

Graficos::~Graficos(){}

void Graficos::DesenhaBase(SDL_Gerenciador sdl_gerenciador, int tamanhoLinha) {
    const int x = centroGrafico.first - xSize/2;
    const int y2 = centroGrafico.second + ySize/2;

    const int y1 = centroGrafico.second - ySize/2;
    const int x1 = centroGrafico.first + xSize/2;

    AlgoritmoBresenham::DesenhaLinha(x, y1, x, y2, sdl_gerenciador.preto, sdl_gerenciador);
    AlgoritmoBresenham::DesenhaLinha(x, y2, x1, y2, sdl_gerenciador.preto, sdl_gerenciador);

    float pixSizeX = UnidadeParaPixel(xSize, PegaVariacaoDoX(), 1);
    float pixSizeY = UnidadeParaPixel(ySize, PegaVariacaoDoY(), 1);

    for(int i=minX+1, cont = 1; i<=maxX; i++,cont++) {
        if(i % TAMANHO_DIV == 0) {
            AlgoritmoBresenham::DesenhaLinha(x + pixSizeX*cont, y1, x + pixSizeX*cont, y2, sdl_gerenciador.cinza, sdl_gerenciador);
            AlgoritmoBresenham::DesenhaLinha(x + pixSizeX*cont, y2, x + pixSizeX*cont, y2-tamanhoLinha, sdl_gerenciador.preto, sdl_gerenciador);
        }
    }
    for(int i=minY+1, cont = 1;i<=maxY;i++, cont++) {
        if(i%TAMANHO_DIV == 0) {
            AlgoritmoBresenham::DesenhaLinha(x,y2 - pixSizeY*cont, x1, y2 - pixSizeY*cont, sdl_gerenciador.cinza, sdl_gerenciador);
            AlgoritmoBresenham::DesenhaLinha(x,y2 - pixSizeY*cont, x+tamanhoLinha, y2 - pixSizeY*cont, sdl_gerenciador.preto, sdl_gerenciador);
        }
    }
}

float Graficos::ResultadoEquacao(float x) {
    if(eqID == 1)
        return EQUACAO1(x);
    else if(eqID == 2)
        return EQUACAO2(x);
    else if(eqID == 3)
        return EQUACAO3(x);
    else if(eqID == 4)
        return EQUACAO4(x);
    else if(eqID == 5)
        return EQUACAO5(x);
    else
        return eqReader.GetEqResult(x);
}


void Graficos::CriarGrafico(SDL_Gerenciador sdl_Gerenciador, Uint32 cor) {

    float x,y;

    for(x = minX;x <= maxX; x += 0.001) {
        y = ResultadoEquacao(x);

        if(y > maxY || y < minY) continue;

        pair<int,int> PontoDoPixel = PegaDeslocamentoDoPonto(pair<float,float>(x,y));
        sdl_Gerenciador.setPixel(PontoDoPixel.first,PontoDoPixel.second,cor);
    }
}

void Graficos::SetEqID(int id)
{
    eqID = id;
}

void Graficos::SetNewEq(string eq)
{
    eqReader.SetEq(eq);
}

void Graficos::CriarGraficos(SDL_Gerenciador sdl_Gerenciador, Uint32 cor[COUNT_EQUACAO]) {

    if(eqID == COUNT_EQUACAO+1)
    {
        for(int i=0; i<COUNT_EQUACAO; i++){
            eqID = i + 1;
            CriarGrafico(sdl_Gerenciador, cor[i]);
        }
        eqID = COUNT_EQUACAO + 1;
    }
    else if(eqID == COUNT_EQUACAO+2)
        CriarGrafico(sdl_Gerenciador, cor[0]);
    else
        CriarGrafico(sdl_Gerenciador, cor[eqID-1]);

    PintaOrigem(sdl_Gerenciador);
}

void Graficos::PintaOrigem(SDL_Gerenciador sdl_Gerenciador)
{
    if(origemGrafico.first < (centroGrafico.first + xSize/2) &&
       origemGrafico.first > (centroGrafico.first - xSize/2) &&
       origemGrafico.second > (centroGrafico.second - ySize/2) &&
       origemGrafico.second < (centroGrafico.second + ySize/2))
        AlgoritmoBresenham::BresenhamCircle
        (origemGrafico.first,origemGrafico.second,3,sdl_Gerenciador.laranja,sdl_Gerenciador);
}

void Graficos::PintarAreaDoGrafico(SDL_Gerenciador sdl_Gerenciador, Uint32 cor) {
    const int startX = centroGrafico.first - xSize/2;
    const int startY = centroGrafico.second - ySize/2;

    for(int i=-1; i<=xSize+1; i++) {
        for(int j=-1; j<=ySize+1; j++) {
            sdl_Gerenciador.setPixel(startX+i,startY+j,cor);
        }
    }
}

void Graficos::MudarVariacao(char direcao) {
    if(direcao == '-') {
        if(clicaMenos == 0) return;
        minX++; maxX--; minY++; maxY--; clicaMenos--; clicaMais++;
    }
    else if(direcao == '+') {
        if(clicaMais == 0) return;
        minX--; maxX++; minY--; maxY++; clicaMenos++; clicaMais--;
    }

    SetaOrigem();
}

int Graficos::PegaVariacaoDoX() {
    return abs(maxX - minX);
}

int Graficos::PegaVariacaoDoY() {
    return abs(maxY - minY);
}

float Graficos::PegaDeslocamentoDoX() {
    return (float)(maxX+minX)/-2.0;
}

float Graficos::PegaDeslocamentoDoY() {
    return (float)(maxY+minY)/2.0;
}

void Graficos:: AlterarOrigem(char direcao) {
    switch(direcao) {
        case 'B':
            minY--; maxY--;
            break;
        case 'C':
            minY++; maxY++;
            break;
        case 'D':
            minX++; maxX++;
            break;
        case 'E':
            minX--; maxX--;
            break;
    }

    SetaOrigem();
}

void Graficos::SetaOrigem() {
    origemGrafico.first = centroGrafico.first + (UnidadeParaPixel(xSize, PegaVariacaoDoX(),1))*PegaDeslocamentoDoX();
    origemGrafico.second = centroGrafico.second + (UnidadeParaPixel(ySize, PegaVariacaoDoY(),1))*PegaDeslocamentoDoY();
}

pair<int,int> Graficos::PegaDeslocamentoDoPonto(pair<float,float> ponto) {
    float newX = (UnidadeParaPixel(xSize, PegaVariacaoDoX(), ponto.first)) + origemGrafico.first;
    float newY = (-UnidadeParaPixel(ySize, PegaVariacaoDoY(), ponto.second)) + origemGrafico.second;

    pair<int,int> newPair(newX, newY);
    return newPair;
}

float Graficos::UnidadeParaPixel(int tamanhoDoGrafico, int tamanhoUnidade, float valor) {
    return valor*tamanhoDoGrafico/tamanhoUnidade;
}

void Graficos::MostraInformacoesConsole() {
    #ifdef WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("\n\n\n\tVariacao do X: %d %d\tVariacao do Y: %d %d\n\tDeslocamento do X: %f \tDeslocamento do Y: %f\n\tMais clicks a esquerda: %d\tMenos Clicks a esquerda: %d\n\n\n",
           minX, maxX, minY, maxY, PegaDeslocamentoDoX(), PegaDeslocamentoDoY(), clicaMais, clicaMenos);
}

