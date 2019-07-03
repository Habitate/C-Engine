#include "Game.h"
#include <iostream>
#include <memory>

#define W 640
#define H 480
#define CENTERED SDL_WINDOWPOS_CENTERED

int main(int argc, char* argv[])
{
    const int fpsCap = 60;
    const constexpr int frameDelay = 1000 / fpsCap; // How many max mileseconds can one frame take up

    int frameTime;
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