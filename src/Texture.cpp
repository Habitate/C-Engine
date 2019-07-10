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


// *************************************
// ***   ---- Texture handler ----   ***
// *************************************
Texture::Texture() : sprites(), spriteIndex(0), visable(true), angle(0), center{0, 0}, flip(SDL_FLIP_NONE), animationStartIndex(0), animating(true), animatingOnce(false){}

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

unsigned int Texture::getIndex(){
    return spriteIndex;
}

void Texture::setIndex(const unsigned int index){
    if(index < count()){
        spriteIndex = index;
    }
    else{
        throw std::out_of_range("Attempted to set an invalid sprite index!");
    }
}

unsigned int Texture::count() const noexcept{
    return sprites.size();
}

//! Returns good if, atleast, the first sprite is valid
bool Texture::good() const noexcept{
    return sprites[spriteIndex]->good();
}

// TODO: Add time frame implementation
void Texture::draw(SDL_Renderer* renderer, const int x, const int y){
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

void Texture::setSize(unsigned int index, int w, int h, bool setAll){
    if(setAll){
        for(std::shared_ptr<TextureData>& sprite : sprites){
            sprite->setSize(w, h);
        }

        return;
    }

    if(index < sprites.size()){
        sprites[index]->setSize(w, h);
    }
    else{
        throw std::out_of_range("Attempted to access a non-existent sprite!");
    }    
}

SDL_Rect& Texture::getSrcRect(unsigned int index, bool getCurrent){
    if(getCurrent){
        return sprites[spriteIndex]->srcRect;
    }

    if(index < count()){
        return sprites[index]->srcRect;
    }
    else{
        throw std::out_of_range("Attempted to access non-existent sprite!");
    }
}
const SDL_Rect& Texture::getSrcRect(unsigned int index, bool getCurrent) const{
    if(getCurrent){
        return sprites[spriteIndex]->srcRect;
    }

    if(index < count()){
        return sprites[index]->srcRect;
    }
    else{
        throw std::out_of_range("Attempted to access non-existent sprite!");
    }
}
SDL_Rect& Texture::getDstRect(unsigned int index, bool getCurrent){
    if(getCurrent){
        return sprites[spriteIndex]->dstRect;
    }

    if(index < count()){
        return sprites[index]->dstRect;
    }
    else{
        throw std::out_of_range("Attempted to access non-existent sprite!");
    }
}
const SDL_Rect& Texture::getDstRect(unsigned int index, bool getCurrent) const{
    if(getCurrent){
        return sprites[spriteIndex]->dstRect;
    }

    if(index < count()){
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
