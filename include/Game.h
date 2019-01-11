#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Text.h"
#include "Object.h"
#include "texture.h"

class Game
{
    public:
        Game(const char* name, int x, int y, int w, int h, int flags);

        void Initialize();

        void HandleSDLEvents();

        void Update();

        void Render();

        void Quit();

        void changeIcon(const char* path);

        bool isRunning();

    private:
        bool running;
        int WREZ, HREZ;

        // Variables
        char input;

        // SDL
        SDL_Event event;
        SDL_Window* window;
        SDL_Renderer* renderer;

        // Text options
        TTF_Font* Sans;
        SDL_Color White;

        // Textures
        Texture t;
};

#endif // GAME_H