#include "texture.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

#include "color.h"
#include "Functions.h"

#include <exception>

//? Data types supported by the SDL_Image library
std::vector<std::string> SUPPORTED_DATA_TYPES = {
	".png", ".jpg", ".jpeg",
    ".bmp", ".gif", ".tga",
    ".pnm", ".pbm", ".pgm",
    ".ppm", ".xpm", ".xcf",
    ".pcx", ".tif", ".tiff",
    ".lbm", ".iff"
};

// *************************************
// ***    ---- Texture data ----     ***
// *************************************
TextureData::TextureData() : sprite(), dstRect{0, 0, 0, 0}, srcRect{0, 0, 0, 0}{}

TextureData::TextureData(SDL_Renderer* const renderer, const std::string& path) : 
sprite(), dstRect{0, 0, 0, 0}, srcRect{0, 0, 0, 0}{
	sprite = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer, path.c_str()), SDL_DestroyTexture);

	if(!sprite){
        throw std::runtime_error("Failed to load sprite!");
	}

	SDL_QueryTexture(sprite.get(), nullptr, nullptr, &srcRect.w, &srcRect.h);
    dstRect = srcRect;

	std::cout << Color(10) << "Successfully loaded sprite: \"" << Color(14) << path << Color(10) << "\"\n" << Color(7);
}

TextureData::TextureData(TextureData& obj) = default;
TextureData& TextureData::operator=(TextureData& obj) = default;

TextureData::TextureData(TextureData&& obj)= default;
TextureData& TextureData::operator=(TextureData&& obj) = default;

void TextureData::setWidth(const int width) noexcept{
	dstRect.w = width;
}
void TextureData::setHeight(const int width) noexcept{
	dstRect.w = width;
}
void TextureData::setDimensions(const int width, const int height) noexcept{
	dstRect.w = width;
	dstRect.h = height;
}
void TextureData::resetDimensions() noexcept{
    dstRect.w = srcRect.w;
    dstRect.h = srcRect.h;
}

void TextureData::draw_ext(SDL_Renderer* const renderer, const int x, const int y, const double& angle, const SDL_Point& center, const SDL_RendererFlip& flip) const{
    if(!sprite){
        throw std::runtime_error("Attempted to draw an uninitialized sprite!");
	}

	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopyEx(renderer, sprite.get(), &srcRect, &dstRect, angle, &center, flip);
}
void TextureData::draw_raw(SDL_Renderer* const renderer, const int x, const int y) const{
	if(!sprite){
        throw std::runtime_error("Attempted to draw an uninitialized sprite!");
	}

	dstRect.x = x;
	dstRect.y = y;

	SDL_RenderCopy(renderer, sprite.get(), &srcRect, &dstRect);
}
void TextureData::draw_static(SDL_Renderer* const renderer) const{
    if(!sprite){
        throw std::runtime_error("Attempted to draw an uninitialized sprite!");
	}

	SDL_RenderCopy(renderer, sprite.get(), &srcRect, &dstRect);
}

//TODO: Implement
bool TextureData::check_collision(const TextureData& sprite) const noexcept{
    
}

bool TextureData::good() const noexcept{
	return (bool)sprite;
}

// *************************************
// ***   ---- Texture handler ----   ***
// *************************************
Sprite::Sprite() : textures(), spriteIndex(0), animationStartIndex(0), animating(true), animatingOnce(false), visable(true){}

void Sprite::load_single(SDL_Renderer* renderer, const std::string& fileName){
    if(!textures.empty()){
        textures.clear();
    }

    textures.emplace_back(new TextureData(renderer, fileName));
}
void Sprite::load_multiple(SDL_Renderer* renderer, const std::string& fileName, const std::string& extension){
    if(!textures.empty()){
        textures.clear();
    }

    std::string fullPath = fileName + '_' + std::to_string(textures.size()) + extension;

    while(fileExists(fullPath)){
        textures.emplace_back(new TextureData(renderer, fullPath));

        fullPath = fileName + '_' + std::to_string(textures.size()) + extension;
    }
}

void Sprite::draw(SDL_Renderer* renderer, const int x, const int y){
    if(!sprites.size() || !visable){
        return;
    }

    if(sprites[spriteIndex]->good()){
        sprites[spriteIndex]->draw(renderer, x, y, angle, &center, flip);
    }

    if(animating){
        ++spriteIndex;
    
        if(spriteIndex == sprites.size()){
            spriteIndex = 0;
        }
    }

    if(animatingOnce){
        if(spriteIndex == animationStartIndex){
            animatingOnce = false;
            animating     = false;
        }
    }
}

void Sprite::setSize(unsigned int index, int w, int h, bool setAll){
    if(setAll){
        for(std::unique_ptr<TextureData>& texture : textures){
            texture->setDimensions(w, h);
        }

        return;
    }

    if(index < textures.size()){
        textures[index]->setDimensions(w, h);
    }
    else{
        throw std::out_of_range("Attempted to access a non-existent sprite!");
    }    
}