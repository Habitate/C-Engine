#include "Game.h"
#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "color.h"

#define W 640
#define H 480

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

    std::cout << C(C::BLUE) << "\n\n-------------- Game started! --------------\n\n" << C();

    std::unique_ptr<Game> game(new Game("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0));

    std::cout << C(C::GREEN) << "\nContructed game! " << C(C::WHITE) << "<Initialized all initial objects>\n\n";

    game->Initialize();
    std::cout << C(C::PINK) << "\nLoaded all objects!\n\n" << C();

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

    std::cout << C(C::BLUE) << "--------------- Game ended! ---------------\n\n" << C();

    return 0;
}