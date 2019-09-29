#pragma once

#include <SDL2/SDL.h>
#include "texture.h"
#include <memory>
#include "input.h"
#include "font.h"
#include "camera.h"
#include "Sprite.h"

class Game{
    public:
        explicit Game(const std::string& name, const int x, const int y, const int w, const int h, const unsigned int flags);

        // Non-Copyable
        Game(const Game& game) = delete;
        Game& operator=(const Game& game) = delete;

        // Non-Moveable
        Game(Game&& game) = delete;
        Game& operator=(Game&& game) = delete;

        ~Game() noexcept;

        //*----------------------------------------------------

        void Initialize();
        void HandleSDLEvents();
        void Update();
        void Render();
        
        void changeIcon(const std::string& path);
        [[nodiscard]] bool isRunning();

    //private:
        bool running;
        int WREZ, HREZ;

        // SDL
        SDL_Event event;
        std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
        std::unique_ptr<SDL_Window  , void(*)(SDL_Window  *)> window;

        // Text options
        SDL_Color White;

        // Textures
        Texture wallpaper;
        Texture ground;

        // Objects
        //std::vector<std::unique_ptr<Object>> objects;

        // Fonts
        Font fnt_ubuntu;

        // Texts
        std::shared_ptr<SDL_Texture> tempText;
        SDL_Rect tempTextSrcRect;
        SDL_Rect tempTextDstRect;

        // Cameras
        Camera camera;
};
