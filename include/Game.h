#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "Object.h"
#include "texture.h"
#include <memory>
#include "InputHandler.h"
#include "Font.h"

class Game{
    public:
        Game(const std::string& name, const int x, const int y, const int w, const int h, const unsigned int flags);
        ~Game();

        void Initialize();
        void HandleSDLEvents();
        void Update();
        void Render();
        
        void changeIcon(const std::string& path);
        bool isRunning();

    private:
        bool running;
        int WREZ, HREZ;

        // SDL
        SDL_Event event;
        std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
        std::unique_ptr<SDL_Window  , void(*)(SDL_Window  *)> window;

        // Text options
        SDL_Color White;

        // Textures
        Sprite wallpaper;
        Sprite ground;

        // Objects
        std::vector<std::unique_ptr<Object>> objects;

        // Fonts
        Font fnt_ubuntu;

        // Texts
        std::shared_ptr<SDL_Texture> tempText;
        SDL_Rect tempTextSrcRect;
        SDL_Rect tempTextDstRect;
};

#endif // GAME_H