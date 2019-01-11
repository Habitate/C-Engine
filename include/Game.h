#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Text.h"
#include "Object.h"
#include "texture.h"
#include <memory>

class Game
{
    public:
        Game(const char* name, int x, int y, int w, int h, int flags);
        ~Game();

        void Initialize();
        void HandleSDLEvents();
        void Update();
        void Render();
        
        void changeIcon(const char* path);
        bool isRunning();

    private:
        bool running;
        int WREZ, HREZ;

        // Variables
        char input;

        // SDL
        SDL_Event event;
        //SDL_Window* window;
        std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
        std::unique_ptr<SDL_Window  , void(*)(SDL_Window  *)> window;

        // Text options
        std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> Sans;
        SDL_Color White;

        // Textures
        Texture t;
};

#endif // GAME_H