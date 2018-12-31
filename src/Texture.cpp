#include "texture.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "color.h"
#include "functions.h"

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
TextureData::TextureData() : sprite(nullptr, SDL_DestroyTexture), visable(true), srcRect({0, 0, 0, 0}), dstRect({0, 0, 0, 0}) {}

void TextureData::Load(SDL_Renderer* renderer, std::string path){
    if(Good()) sprite.reset();

    sprite = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(IMG_LoadTexture(renderer, path.c_str()), SDL_DestroyTexture);

    if(!Good()){
        std::cout << Color(12) << "Error loading: \"" << Color(14) << path << Color(12) << "\"\n" << Color(7);
        std::cout << "\t-> " << IMG_GetError() << '\n';
        
        return;
    }

    SDL_QueryTexture(sprite.get(), nullptr, nullptr, &srcRect.w, &srcRect.h);
    dstRect = srcRect;

    std::cout << Color(10) << "Successfully loaded: \"" << Color(14) << path << Color(10) << "\"\n" << Color(7);
}

void TextureData::Draw(SDL_Renderer* renderer, int x, int y){
    if(!Good() || !visable) return;

    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopy(renderer, sprite.get(), &srcRect, &dstRect);
}

void TextureData::ChangeSize(int w, int h){
    if(w >= 0) dstRect.w = w;
    if(h >= 0) dstRect.h = h;
}

bool TextureData::Good(){
    return (bool)sprite;
}




// *************************************
// ***   ---- Texture handler ----   ***
// *************************************
Texture::Texture() : spriteIndex(0), visable(true) {}

void Texture::Load(SDL_Renderer* renderer, std::string fileName){
    std::vector<std::string>* DATA_TYPES = &SUPPORTED_DATA_TYPES;
    std::vector<std::string> singleType(1);

    if(cutExtension(fileName, singleType[0])) DATA_TYPES = &singleType;

    for(std::string ext : *DATA_TYPES){
		if(fileExists(fileName        + ext)){ SingleLoad(renderer, fileName + ext); return; } //? Loads single   file
		if(fileExists(fileName + "_0" + ext)){  MultiLoad(renderer, fileName,  ext); return; } //? Loads multiple files
	}
    
    std::cout << "Unable to find a suitable file for: " << fileName + singleType[0] << '\n';  
}

void Texture::SingleLoad(SDL_Renderer* renderer, std::string fileName){
    sprites.emplace_back(new TextureData);
    sprites[sprites.size() - 1]->Load(renderer, fileName);
}

void Texture::MultiLoad(SDL_Renderer* renderer, std::string fileName, std::string extension){
    while(fileExists(fileName + '_' + std::to_string(sprites.size()) + extension)){
        sprites.emplace_back(new TextureData);
        sprites[sprites.size() - 1]->Load(renderer, fileName + '_' + std::to_string(sprites.size() - 1) + extension);
    }
}

int Texture::getSpriteCount(){
    return sprites.size();
}

//! Returns good if, atleast, the first sprite is valid
bool Texture::Good(){
    if(getSpriteCount()) return sprites[0]->Good();
    return false;
}

// TODO: Add time frame implementation
void Texture::Draw(SDL_Renderer* renderer, int x, int y){
    if(!sprites.size()) return;

    if(sprites[spriteIndex]->Good()) sprites[spriteIndex]->Draw(renderer, x, y);

    ++spriteIndex;
    if(spriteIndex == sprites.size()) spriteIndex = 0;
}

void Texture::ChangeSize(int index, int w, int h){
    if(index == sprites.size()) return;
    
    if(index == -1)
        for(int i = 0; i < sprites.size(); ++i)
            sprites[i]->ChangeSize(w, h);
    else
        sprites[index]->ChangeSize(w, h);
}