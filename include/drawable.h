#pragma once

#include <SDL2/SDL.h>
#include "camera.h"

class Drawable{
    public:
        Drawable();
        Drawable(SDL_Renderer* const renderer);

        // Copyable
        Drawable(const Drawable& obj) noexcept;
        Drawable& operator=(const Drawable& obj) noexcept;
        
        // Moveable
        Drawable(Drawable&& obj) noexcept;
        Drawable& operator=(Drawable&& obj) noexcept;

        virtual ~Drawable() = 0;

        //*----------------------------------------------------

        virtual void draw(const Camera& camera = {}, const SDL_Point& coords = {0, 0}, const double& angle = 0, const SDL_Point* const center = nullptr, const SDL_RendererFlip& flip = SDL_FLIP_NONE) const = 0;

        [[nodiscard]] SDL_Renderer* get_renderer() const noexcept;
        virtual void  set_renderer(SDL_Renderer* const renderer) = 0;

    protected:
        SDL_Renderer* renderer;
};