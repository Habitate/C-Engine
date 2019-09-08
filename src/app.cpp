#include "game.h"
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

    //SDL_SetRelativeMouseMode(SDL_TRUE);
    
    const int fps_cap = 60;
    const constexpr Uint32 frame_delay = 1000 / fps_cap; // How many max mileseconds can one frame take up

    Uint32 frame_time, frame_start;

    std::cout << C(C::BLUE) << "\n\n-------------- Game started! --------------\n\n" << C();

    std::unique_ptr<Game> game(new Game("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0));

    std::cout << C(C::GREEN) << "\nContructed game! " << C(C::WHITE) << "<Initialized all initial objects>\n\n";

    game->Initialize();
    std::cout << C(C::PINK) << "\nLoaded all objects!\n\n" << C();

    while(game->isRunning()){
        frame_start = SDL_GetTicks();

        //!----------------------
        game->HandleSDLEvents();
        game->Update();
        game->Render();
        //!----------------------

        frame_time = SDL_GetTicks() - frame_start;
        
        SDL_Delay(frame_delay > frame_time ? frame_delay - frame_time : 0);
    }

    std::cout << C(C::BLUE) << "--------------- Game ended! ---------------\n\n" << C();

    return 0;
}