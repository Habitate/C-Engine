#include "texture.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <exception>
#include <array>
#include <algorithm>

#include "color.h"
#include "functions.h"

Texture::Texture() noexcept : imageData(), dstRect{0, 0, 0, 0}, srcRect{0, 0, 0, 0}{}
Texture::Texture(SDL_Renderer* const renderer, const std::string& path) : Texture(){
	load(renderer, path);
}
Texture::~Texture() = default;

Texture::Texture(Texture& obj) noexcept = default;
Texture& Texture::operator=(Texture& obj) noexcept = default;

Texture::Texture(Texture&& obj) noexcept = default;
Texture& Texture::operator=(Texture&& obj) noexcept = default;

void Texture::load(SDL_Renderer* const renderer, const std::string& path){
    imageData = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer, path.c_str()), SDL_DestroyTexture);

	if(!imageData){
		std::cout << C(C::RED) << "Failed to load image: " << C(C::YELLOW) << path << "\"\n" << C();
		std::string errorMSG;

		if(!file_exists(path)){
			errorMSG += "File doesn't exist!\n";
		}

		const std::string extension = get_extension(path);

		if(extension.empty()){
			errorMSG += "\t   File does not contain an extension!\n";
		}
		else{
			std::array<std::string, 17>::const_iterator ext = std::find(SUPPORTED_DATA_TYPES.begin(), SUPPORTED_DATA_TYPES.end(), extension);

			if(ext == SUPPORTED_DATA_TYPES.end()){
				errorMSG += "\t   Invalid file extension! \"" + extension + '\"';
			}
		}

        throw std::runtime_error(errorMSG);
	}
	else{
		std::cout << C(C::GREEN) << "Successfully loaded image: " << C(C::YELLOW) << "\"" << path << "\"\n" << C();
	}

	SDL_QueryTexture(imageData.get(), nullptr, nullptr, &srcRect.w, &srcRect.h);
    dstRect = srcRect;
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

void Texture::draw_ext(SDL_Renderer* const renderer, const int x, const int y, const double& angle, const SDL_Point* const center, const SDL_RendererFlip& flip) const{
    if(!imageData){
        throw std::runtime_error(std::string("Attempted to draw an uninitialized texture! Object: ") + std::to_string((int)(void*)this) + '\n');
	}

	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopyEx(renderer, imageData.get(), &srcRect, &dstRect, angle, center, flip);
}
void Texture::draw_raw(SDL_Renderer* const renderer, const int x, const int y) const{
	if(!imageData){
        throw std::runtime_error(std::string("Attempted to draw an uninitialized texture! Object: ") + std::to_string((int)(void*)this) + '\n');
	}

	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopy(renderer, imageData.get(), &srcRect, &dstRect);
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

//? Data types supported by the SDL_Image library
const std::array<std::string, 17> Texture::SUPPORTED_DATA_TYPES = {
	".png", ".jpg", ".jpeg",
    ".bmp", ".gif", ".tga",
    ".pnm", ".pbm", ".pgm",
    ".ppm", ".xpm", ".xcf",
    ".pcx", ".tif", ".tiff",
    ".lbm", ".iff"
};