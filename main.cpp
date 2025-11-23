
#include "SDL_Gerenciador.h"
#include "Graficos.h"
#include "AlgoritmoBresenham.h"

#include <unistd.h>

#include <thread>

#define DURACAO usleep(1000)

#define EQUACAO1(x) x
#define EQUACAO2(x) -x
#define EQUACAO3(x) 2*x*x-6*x+1
#define EQUACAO4(x) sin(x)
#define EQUACAO5(x) -(x*x)+4

void ClearConsole()
{
    #ifdef WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Menu()
{
    printf("1- y = x\n2- y = -x\n3- y = 2*x*x-6*x+1\n4- sin(x)\n5- -(x*x)+4\n6- Todos os graficos\n7- Eq nova");
}


void MostraGraficos(SDL_Gerenciador sdl_gerenciador, Graficos *graficos) {

    graficos->PintarAreaDoGrafico(sdl_gerenciador, sdl_gerenciador.cinzaClaro);

    graficos->DesenhaBase(sdl_gerenciador, 10);

    Uint32 cores[] = {sdl_gerenciador.vermelho, sdl_gerenciador.verde, sdl_gerenciador.amarelo, sdl_gerenciador.azul, sdl_gerenciador.roxo};

    graficos->CriarGraficos(sdl_gerenciador, cores);
}

bool readConsole = false;

void EqRequest(Graficos *graficos,SDL_Gerenciador sdl_gerenciador)
{
    readConsole = true;
    ClearConsole();
    printf("\nDigite uma equacao: ");
    string eq;
    cin >> eq;
    graficos->SetNewEq(eq);
    graficos->SetEqID(7);
    ClearConsole();
    Menu();

    MostraGraficos(sdl_gerenciador,graficos);
    readConsole = false;
}

int main() {
    Menu();
    SDL_Gerenciador sdl_gerenciador(800, 600, "Graficos");

    Graficos graficos(pair<int,int>(sdl_gerenciador.width/2, sdl_gerenciador.height/2), 550, 550, -10, 10, 20, 8);

    MostraGraficos(sdl_gerenciador, &graficos);

    bool teclas = false;
    bool executando = true;

    while (executando) {
        while (sdl_gerenciador.GetPollEvent()) {
            if (sdl_gerenciador.evento.type == SDL_QUIT) exit(0);

            if(sdl_gerenciador.evento.type == SDL_MOUSEMOTION) {
                std::stringstream ss;
                ss << sdl_gerenciador.tit << " X: " << sdl_gerenciador.evento.motion.x << " Y: " << sdl_gerenciador.evento.motion.y;
                sdl_gerenciador.ChangeWindowTitle(ss.str().c_str());
            }

            if (sdl_gerenciador.evento.type == SDL_KEYDOWN) {
                if(teclas) continue;

                graficos.PintarAreaDoGrafico(sdl_gerenciador, sdl_gerenciador.branco);

                // Teclas - e +: pode ser a do teclado numérico ou o outro
                if(sdl_gerenciador.evento.key.keysym.sym == SDLK_MINUS || sdl_gerenciador.evento.key.keysym.sym == SDLK_KP_MINUS)
                    graficos.MudarVariacao('-');
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_PLUS || sdl_gerenciador.evento.key.keysym.sym == SDLK_KP_PLUS)
                    graficos.MudarVariacao('+');


                // Teclas cima, baixo, direita, esquerda
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_UP) graficos.AlterarOrigem('C');
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_DOWN) graficos.AlterarOrigem('B');
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_RIGHT) graficos.AlterarOrigem('D');
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_LEFT) graficos.AlterarOrigem('E');

                //id função
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_1) graficos.SetEqID(1);
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_2) graficos.SetEqID(2);
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_3) graficos.SetEqID(3);
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_4) graficos.SetEqID(4);
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_5) graficos.SetEqID(5);
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_6) graficos.SetEqID(6); //print todas eq
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_7 && !readConsole) //leitura de uma nova eq
                    std::thread{EqRequest,&graficos,sdl_gerenciador}.detach();

                // Espaço fecha o programa
                else if(sdl_gerenciador.evento.key.keysym.sym == SDLK_SPACE) executando = false;

                MostraGraficos(sdl_gerenciador,&graficos);

                teclas = true;
            }

            if (sdl_gerenciador.evento.type == SDL_KEYUP) teclas = false;
        }

        DURACAO;

        sdl_gerenciador.UpdateWindow();
    }

    return 0;
}
