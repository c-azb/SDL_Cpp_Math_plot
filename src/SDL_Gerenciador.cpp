#include "SDL_Gerenciador.h"

SDL_Gerenciador::SDL_Gerenciador(int sizeX, int sizeY, string titulo) {
    tit = titulo;
    InicializeSDL(sizeX,sizeY);
}

SDL_Gerenciador::~SDL_Gerenciador(){}


void SDL_Gerenciador::InicializeSDL(int sizeX,int sizeY) {

    setlocale(LC_ALL, NULL);

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(tit.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,sizeX, sizeY,SDL_WINDOW_RESIZABLE);

    window_surface = SDL_GetWindowSurface(window);

    pixels = (unsigned int *) window_surface->pixels;
    width = window_surface->w;
    height = window_surface->h;

    SetFullScreenColor(RGB(255,255,255));
}

void SDL_Gerenciador::setPixel(int x, int y, Uint32 cor) {
    if((x<0 || x>=width || y<0 || y>=height)) return;

    pixels[x + y * width] = cor;
}


Uint32 SDL_Gerenciador::RGB(int r, int g, int b, int a) {
    return SDL_MapRGBA(window_surface->format, r, g, b, a);
}

Uint32 SDL_Gerenciador::RGB(int r, int g, int b) {
    return SDL_MapRGBA(window_surface->format, r, g, b, 255);
}

Uint32 SDL_Gerenciador::getPixel(int x, int y) {
    if((x>=0 && x<=width) && (y>=0 && y<=height))
        return pixels[x + width * y];
    else
        return -1;
}

void SDL_Gerenciador::OnResizeWindow() {
    window_surface = SDL_GetWindowSurface(window);
    pixels = (unsigned int *) window_surface->pixels;
    width = window_surface->w;
    height = window_surface->h;
    printf("Size changed: %d, %d\n", width, height);
}

void SDL_Gerenciador::SetFullScreenColor(Uint32 cor) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            setPixel(x, y, cor);
        }
    }
}

void SDL_Gerenciador::ChangeWindowTitle(const char *novoTitulo) {
    SDL_SetWindowTitle(window, novoTitulo);
}

void SDL_Gerenciador::UpdateWindow() {
    SDL_UpdateWindowSurface(window);
}

int SDL_Gerenciador::GetPollEvent() {
    return SDL_PollEvent(&evento);
}

