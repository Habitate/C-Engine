#include "texture.h"

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

//? Data types supported by the SDL_Image library
const std::array<std::string, 17> Texture::SUPPORTED_DATA_TYPES = {
	".png", ".jpg", ".jpeg",
    ".bmp", ".gif", ".tga",
    ".pnm", ".pbm", ".pgm",
    ".ppm", ".xpm", ".xcf",
    ".pcx", ".tif", ".tiff",
    ".lbm", ".iff"
};

Texture::Texture() noexcept : Drawable(), imageData(), dstRect{0, 0, 0, 0}, srcRect{0, 0, 0, 0}{}
Texture::Texture(SDL_Renderer* const renderer, const std::string& path) : Drawable(renderer), imageData(), dstRect{0, 0, 0, 0}, srcRect{0, 0, 0, 0}{
	load(path);
}

Texture::Texture(const Texture& obj) noexcept = default;
Texture& Texture::operator=(const Texture& obj) noexcept = default;

Texture::Texture(Texture&& obj) noexcept = default;
Texture& Texture::operator=(Texture&& obj) noexcept = default;

Texture::~Texture() noexcept = default;

//*----------------------------------------------------

void Texture::load(const std::string& path){
    imageData = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer, path.c_str()), SDL_DestroyTexture);

	if(!imageData){
		std::cout << C(C::RED) << "Failed to load image: " << C(C::YELLOW) << path << "\"\n" << C();
		std::string error_msg;

		if(!file_exists(path)){
			error_msg += "File doesn't exist!\n";
		}

		if(!exists(std::begin(SUPPORTED_DATA_TYPES), std::end(SUPPORTED_DATA_TYPES), get_extension(path))){
			error_msg += "\t   No valid extension found!\n";
		}

        throw std::runtime_error(error_msg);
	}
	else{
		std::cout << C(C::GREEN) << "Successfully loaded image: " << C(C::YELLOW) << "\"" << path << "\"\n" << C();
	}

	SDL_QueryTexture(imageData.get(), nullptr, nullptr, &srcRect.w, &srcRect.h);
    dstRect = srcRect;
}

void Texture::set_renderer(SDL_Renderer* const renderer){
	this->renderer = renderer;

	imageData.reset();
}

void Texture::set_width(const int width) noexcept{
	dstRect.w = width;
}
void Texture::set_height(const int width) noexcept{
	dstRect.w = width;
}
void Texture::set_dimensions(const int width, const int height) noexcept{
	dstRect.w = width;
	dstRect.h = height;
}

void Texture::reset_dimensions() noexcept{
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
}
void Texture::reset_width() noexcept{
    dstRect.w = srcRect.w;
}
void Texture::reset_height() noexcept{
    dstRect.h = srcRect.h;
}

void Texture::draw(const Camera& camera, const SDL_Point& coords, const double& angle, const SDL_Point* const center, const SDL_RendererFlip& flip) const{
	if(!imageData){
        throw std::runtime_error(std::string("Attempted to draw an uninitialized texture! Object: ") + static_cast<const void*>(this) + '\n');
	}

	dstRect.x = coords.x;
	dstRect.y = coords.y;
	SDL_Rect dest = camera.get_dst_view(dstRect);
	
	SDL_RenderCopyEx(renderer, imageData.get(), &srcRect, &dest, angle, center, flip);
}

bool Texture::check_collision(const Texture& texture) const noexcept{
    return SDL_HasIntersection(&dstRect, &texture.get_dst_rect()) == SDL_TRUE;
}

const SDL_Rect& Texture::get_src_rect() const noexcept{
	return srcRect;
}
const SDL_Rect& Texture::get_dst_rect() const noexcept{
	return dstRect;
}

bool Texture::good() const noexcept{
	return (bool)imageData;
}
