#include "drawable.h"

Drawable::Drawable() : renderer(nullptr){}
Drawable::Drawable(SDL_Renderer* const renderer) : renderer(renderer){}

Drawable::Drawable(const Drawable& obj) noexcept = default;
Drawable& Drawable::operator=(const Drawable& obj) noexcept = default;

Drawable::Drawable(Drawable&& obj) noexcept = default;
Drawable& Drawable::operator=(Drawable&& obj) noexcept = default;

Drawable::~Drawable() noexcept {}

//*----------------------------------------------------

SDL_Renderer* Drawable::get_renderer() const noexcept{
    return renderer;
}