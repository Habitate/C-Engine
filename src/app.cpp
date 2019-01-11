#include "Game.h"
#include <iostream>

#define W 640
#define H 480
#define CENTER SDL_WINDOWPOS_CENTERED

int main(int argc, char* argv[])
{
    const int fpsCap = 60;
    const int frameDelay = 1000 / fpsCap;

    int frameTime;
    Uint32 frameStart;

    Game* game = new Game("Engine", CENTER, CENTER, W, H, SDL_WINDOW_RESIZABLE);
    std::cout << "Initialized framework!\n\n";

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
        if(frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);  
    } delete game;
    
    return 0;
}