#ifndef GRAFICOS_H
#define GRAFICOS_H

#include "AlgoritmoBresenham.h"
#include "SDL_Gerenciador.h"

#include <math.h>
#include <iostream>

#include "EqReader.h"

using namespace std;

class Graficos {

    public:
        Graficos(pair<int,int> centro, int xSizeSet, int ySizeSet, int minXSet, int maxXset, int teclaMais, int teclaMenos);
        virtual ~Graficos();

        void CriarGrafico(SDL_Gerenciador sdl_Gerenciador, Uint32 cor);
        void CriarGraficos(SDL_Gerenciador sdl_Gerenciador, Uint32 cor[]);

        void DesenhaBase(SDL_Gerenciador sdl_gerenciador, int tamanhoLinha);

        void PintarAreaDoGrafico(SDL_Gerenciador sdl_Gerenciador, Uint32 cor);

        void MudarVariacao(char direcao);
        void AlterarOrigem(char direcao);

        void MostraInformacoesConsole();
        void SetEqID(int id);
        void SetNewEq(string eq);
    protected:

    private:
        pair<int,int> centroGrafico;
        pair<int,int> origemGrafico;

        int xSize, ySize;
        int minX, maxX;
        int minY, maxY;

        int clicaMais, clicaMenos;

        int PegaVariacaoDoX();
        int PegaVariacaoDoY();

        float PegaDeslocamentoDoX();
        float PegaDeslocamentoDoY();

        void PintaOrigem(SDL_Gerenciador sdl_Gerenciador);

        void SetaOrigem();

        float ResultadoEquacao(float x);

        pair<int,int> PegaDeslocamentoDoPonto(pair<float,float> ponto);
        float UnidadeParaPixel(int tamanhoDoGrafico, int tamanhoUnidade, float valor);

        int eqID = 1;
        EqReader eqReader;
};

#endif
