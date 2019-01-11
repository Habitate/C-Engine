// Game defines
#define W 640
#define H 480

#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
    int fpsCap = 60;
    int frameDelay = 1000 / fpsCap;
    int frameTime;

    Uint32 frameStart;

    Game* game = new Game("Engine",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        W, H, 0);

    game->Initialize();

    while( game->isRunning() ){
        frameStart = SDL_GetTicks();

        // Actual game loop
        
        game->HandleSDLEvents();
        game->Update();
        game->Render();

        // Etc

        frameTime = SDL_GetTicks() - frameStart; 
        if(frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);  

    } game->Quit();

    return 0;
}