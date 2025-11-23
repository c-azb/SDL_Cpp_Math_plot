#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <sstream>

#ifndef SDL_GERENCIADOR_H
#define SDL_GERENCIADOR_H

using namespace std;


class SDL_Gerenciador {

    public:
        SDL_Gerenciador(int sizeX, int sizeY, string titulo);
        virtual ~SDL_Gerenciador();

        SDL_Event evento;
        int width, height;
        string tit = "SDL Pontos";


        void setPixel(int x, int y, Uint32 cor);
        Uint32 RGB(int r, int g, int b, int a);
        Uint32 RGB(int r, int g, int b);
        Uint32 getPixel(int x, int y);
        void OnResizeWindow();
        void SetFullScreenColor(Uint32 cor);
        void ChangeWindowTitle(const char *novoTitulo);
        void UpdateWindow();
        int GetPollEvent();

        const Uint32 preto = 0x000000;
        const Uint32 vermelho = 0xFF0000;
        const Uint32 branco = 0xFFFFFF;
        const Uint32 verde = 0x008000;
        const Uint32 azul = 0x0000FF;
        const Uint32 roxo = 0x800080;
        const Uint32 amarelo = 0xFFFF00;
        const Uint32 laranja = 0xFF8C00;
        const Uint32 cinza = 0xC0C0C0;
        const Uint32 cinzaClaro = 0xf0f0f0;

    protected:

    private:
        unsigned int * pixels;
        SDL_Surface * window_surface;
        SDL_Renderer * renderer;
        SDL_Window * window;
        void InicializeSDL(int sizeX, int sizeY);
};

#endif
