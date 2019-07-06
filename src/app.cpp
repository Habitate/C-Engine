#include "Game.h"
#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define W 640
#define H 480
#define CENTERED SDL_WINDOWPOS_CENTERED

int main(int argc, char* argv[]){
    //Referenc argc and argv to get rid of unused variable warnings
    argc += 1 - 1;
    argv += 1 - 1;

    //Initialize SDL_*
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    TTF_Init();
    
    const int fpsCap = 60;
    const constexpr Uint32 frameDelay = 1000 / fpsCap; // How many max mileseconds can one frame take up

    Uint32 frameTime;
    Uint32 frameStart;

    std::unique_ptr<Game> game(new Game("Engine", CENTERED, CENTERED, W, H, SDL_WINDOW_RESIZABLE));

    std::cout << "Contructed game! <Initialized framework>\n\n";

    game->Initialize();
    std::cout << "\nInitialized all objects!\n\n";

    while(game->isRunning()){
        frameStart = SDL_GetTicks();

        //!----------------------
        game->HandleSDLEvents();
        game->Update();
        game->Render();
        //!----------------------

        frameTime = SDL_GetTicks() - frameStart;
        
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}