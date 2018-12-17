#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Text.h"
#include "Object.h"

class Game
{
    public:
        Game();
        ~Game();

        // Text --->
        void InitializeTexts();
        void DoThingsBasedOnInputTexts(char input);
        void UpdateTexts();
        void RenderTexts();

        // Objects --->
        void InitializeObjects();
        void DoThingsBasedOnInputObjects(char input);
        void UpdateObjects();
        void RenderObjects();

        // -------------- //

        void Initialize(const char* name, int x, int y, int w, int h, int flags);

        void HandleSDLEvents();

        void Update();

        void Render();

        void Quit();

        void changeIcon(const char* path);

        bool isRunning();

    private:
        bool running, connectedToServer;

        // Variables
        char input;

        // SDL
        SDL_Event event;
        SDL_Window* window;
        SDL_Renderer* renderer;

        // Internet
        SOCKET DataSocket;

        // Text options
        TTF_Font* Sans;
        SDL_Color White;
            
        Text greet;

        Object object1, object2;
};

#endif // GAME_H