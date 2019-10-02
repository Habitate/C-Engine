#include "image.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <exception>
#include <array>
#include <algorithm>

#include "camera.h"
#include "color.h"
#include "functions.h"
#include "camera.h"

#include "constants.h"

Image::Image() noexcept : Drawable(), texture(), dstRect{0, 0, 0, 0}, srcRect{0, 0, 0, 0}{}
Image::Image(SDL_Renderer* const renderer, const std::string& path) : Drawable(renderer), texture(), dstRect{0, 0, 0, 0}, srcRect{0, 0, 0, 0}{
	load(path);
}

Image::Image(const Image& obj) noexcept = default;
Image& Image::operator=(const Image& obj) noexcept = default;

Image::Image(Image&& obj) noexcept = default;
Image& Image::operator=(Image&& obj) noexcept = default;

Image::~Image() noexcept = default;

//*----------------------------------------------------

void Image::load(const std::string& path){
    texture = load_texture(renderer, path);

	SDL_QueryTexture(texture.get(), nullptr, nullptr, &srcRect.w, &srcRect.h);
    dstRect = srcRect;
}

void Image::set_renderer(SDL_Renderer* const renderer){
	this->renderer = renderer;

	texture.reset();
}

void Image::set_dimensions(const int width, const int height) noexcept{
	dstRect.w = width;
	dstRect.h = height;
}
void Image::set_width(const int width) noexcept{
	dstRect.w = width;
}
void Image::set_height(const int height) noexcept{
	dstRect.h = height;
}

void Image::reset_dimensions() noexcept{
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
}
void Image::reset_width() noexcept{
    dstRect.w = srcRect.w;
}
void Image::reset_height() noexcept{
    dstRect.h = srcRect.h;
}

void Image::draw(const Camera& camera, const SDL_Point& coords, const double& angle, const SDL_Point* const center, const SDL_RendererFlip& flip) const{
	if(!texture){
        throw std::runtime_error(std::string("Attempted to draw an uninitialized image! Object: ") + static_cast<const void*>(this) + '\n');
	}

	dstRect.x = coords.x;
	dstRect.y = coords.y;
	SDL_Rect dest = camera.get_dst_view(dstRect);
	
	SDL_RenderCopyEx(renderer, texture.get(), &srcRect, &dest, angle, center, flip);
}
/*
bool Image::check_collision(const Image& image) const noexcept{
    return SDL_HasIntersection(&dstRect, &image.get_dst_rect()) == SDL_TRUE;
}
*/
const SDL_Rect& Image::get_src_rect() const noexcept{
	return srcRect;
}
const SDL_Rect& Image::get_dst_rect() const noexcept{
	return dstRect;
}

bool Image::good() const noexcept{
	return (bool)texture;
}
