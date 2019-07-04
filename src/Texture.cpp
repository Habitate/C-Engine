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
TextureData::TextureData(SDL_Renderer* renderer, std::string path) : sprite(nullptr, SDL_DestroyTexture), visable(true), srcRect({0, 0, 0, 0}), dstRect({0, 0, 0, 0}){
    sprite = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(IMG_LoadTexture(renderer, path.c_str()), SDL_DestroyTexture);

    if(!good()){
        std::cout << Color(12) << "Error loading: \"" << Color(14) << path << Color(12) << "\"\n" << Color(7);
        std::cout << "\t-> " << IMG_GetError() << '\n';
        
        return;
    }

    SDL_QueryTexture(sprite.get(), nullptr, nullptr, &srcRect.w, &srcRect.h);
    dstRect = srcRect;

    std::cout << Color(10) << "Successfully loaded: \"" << Color(14) << path << Color(10) << "\"\n" << Color(7);
}

void TextureData::draw(SDL_Renderer* renderer, int x, int y){
    if(!good() || !visable) return;

    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopy(renderer, sprite.get(), &srcRect, &dstRect);
}

void TextureData::setSize(int w, int h){
    if(w >= 0) dstRect.w = w;
    if(h >= 0) dstRect.h = h;
}

bool TextureData::good(){
    return (bool)sprite;
}



// *************************************
// ***   ---- Texture handler ----   ***
// *************************************
Texture::Texture() : spriteIndex(0), visable(true), animating(true), animatingOnce(false){}

void Texture::load(SDL_Renderer* renderer, std::string fileName){
    std::vector<std::string>* DATA_TYPES = &SUPPORTED_DATA_TYPES;
    std::vector<std::string> singleType(1);

    if(cutExtension(fileName, singleType[0])){
        DATA_TYPES = &singleType;
    }

    for(std::string ext : *DATA_TYPES){
		if(fileExists(fileName        + ext)){ //? Loads a single file
            SingleLoad(renderer, fileName + ext);
            return;
        }

		if(fileExists(fileName + "_0" + ext)){ //? Loads multiple files
            MultiLoad(renderer, fileName,  ext);
            return;
        } 
	}
    
    std::cout << "Unable to find a suitable file for: " << fileName + singleType[0] << '\n';  
}

int Texture::getIndex(){
    return spriteIndex;
}

void Texture::setIndex(const int index){
    if(index < count() && index >= 0){
        spriteIndex = index;
    }
    else{
        throw std::out_of_range("Attempted to set an invalid sprite index!");
    }
}

int Texture::count() const{
    return sprites.size();
}

//! Returns good if, atleast, the first sprite is valid
bool Texture::good() const{
    return sprites[spriteIndex]->good();
}

// TODO: Add time frame implementation
void Texture::draw(SDL_Renderer* renderer, int x, int y){
    if(!sprites.size() || !visable){
        return;
    }

    if(sprites[spriteIndex]->good()){
        sprites[spriteIndex]->draw(renderer, x, y);
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

void Texture::setSize(int index, int w, int h){
    if(index == sprites.size() || index < -1){
        throw std::out_of_range("Attempted to access a non-existent sprite!");
    }
    
    if(index == -1){
        for(int i = 0; i < sprites.size(); ++i){
            sprites[i]->setSize(w, h);
        }
    }
    else{
        sprites[index]->setSize(w, h);
    }
}

SDL_Rect& Texture::getSrcRect(int index){
    if(index == -1){
        return sprites[spriteIndex]->srcRect;
    }

    if(index < count() && index >= 0){
        return sprites[index]->srcRect;
    }
    else{
        throw std::out_of_range("Attempted to access non-existent sprite!");
    }
}
SDL_Rect& Texture::getDstRect(int index){
    if(index == -1){
        return sprites[spriteIndex]->dstRect;
    }

    if(index < count() && index >= 0){
        return sprites[index]->dstRect;
    }
    else{
        throw std::out_of_range("Attempted to access non-existent sprite!");
    }
}

void Texture::startAnimation(){
	animating = true;
}
void Texture::stopAnimation(){
	animating = false;
}
void Texture::resetAnimation(){
	setIndex(animationStartIndex);
}
void Texture::runAnimationOnce(){
    animatingOnce = true;
    resetAnimation();
    startAnimation();
}

void Texture::SingleLoad(SDL_Renderer* renderer, const std::string& fileName){
    sprites.emplace_back(new TextureData(renderer, fileName));
}
void Texture::MultiLoad(SDL_Renderer* renderer, const std::string& fileName, const std::string& extension){
    while(fileExists(fileName + '_' + std::to_string(sprites.size()) + extension)){
        sprites.emplace_back(new TextureData(renderer, fileName + '_' + std::to_string(sprites.size()) + extension));
    }
}
