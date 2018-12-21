#include "texture.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "color.h"

#include <sys/stat.h> //* Used for file checking

// -- Texture -- //
Texture::Texture() : sprite(nullptr), good(false), visable(true), srcRect({0, 0, 0, 0}), dstRect({0, 0, 0, 0}) {}

Texture::~Texture(){
    if(sprite) SDL_DestroyTexture(sprite);
    good = false;
}

void Texture::Load(SDL_Renderer* renderer, std::string path){
    if(sprite) SDL_DestroyTexture(sprite);

    sprite = IMG_LoadTexture(renderer, path.c_str());

    if(!sprite){
        std::cout << Color(12) << "Error loading: \"" << Color(14) << path << Color(12) << "\"\n" << Color(7);
        std::cout << "\t-> " << IMG_GetError() << '\n';
        
        return;
    }

    SDL_QueryTexture(sprite, nullptr, nullptr, &srcRect.w, &srcRect.h);
    dstRect.w = srcRect.w; dstRect.h = srcRect.h;

    std::cout << Color(10) << "Successfully loaded: \"" << Color(14) << path << Color(10) << "\"\n" << Color(7);
    good = true;
}

void Texture::Draw(SDL_Renderer* renderer, int x, int y){
    if(!good && !visable) return;

    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopy(renderer, sprite, &srcRect, &dstRect);
}

//* Pass -1 to keep the same value
void Texture::ChangeSize(int w, int h){
    if(w >= 0) dstRect.w = w;
    if(h >= 0) dstRect.h = h;
}

inline bool fileExists(std::string path) {
    struct stat buffer;  
    return (stat(path.c_str(), &buffer) == 0);
}

// TODO: Add support for paths like "assets/myImage.png"
std::string resolveExtension(std::string path){
    const char* fileTypes[17] = {
        "png", "jpg", "jpeg",
        "bmp", "gif", "tga",
        "pnm", "pbm", "pgm",
        "ppm", "xpm", "xcf",
        "pcx", "tif", "tiff",
        "lbm", "iff"
    };

    // Test for all supported file types
    for(std::string ext : fileTypes){
        if(fileExists(path + "_0." + ext)){
            return ext;
            break;
        }
    }

    std::string ext;
    return ext;
}

// -- Multi-Texture -- //
MultiTexture::MultiTexture() : spriteIndex(0), spriteCount(0), timeFrame(0), visable(true) {}

MultiTexture::~MultiTexture(){}

// !: Currently only works with paths like "../myImage"
void MultiTexture::Load(SDL_Renderer* renderer, std::string path){
    std::string ext = resolveExtension(path);
    if(ext.empty()){
        std::cout << Color(12) << "Error loading sprites for: \"" << Color(14) << path << Color(12) << "\"\n" << Color(7);
        return;
    }

    while(fileExists(path + '_' + std::to_string(spriteCount) + '.' + ext)){
        sprites.push_back(new Texture);
        sprites[spriteCount]->Load(renderer, path + '_' + std::to_string(spriteCount) + '.' + ext);
        
        ++spriteCount;
    }

    std::cout << Color(10) << "Loaded " << Color(13) << spriteCount << Color(10) << " sprites for \""
    << Color(14) << path << Color(10) << "\"\n" << Color(7);
}

// TODO: Add time frame implementation
void MultiTexture::Draw(SDL_Renderer* renderer, int x, int y){
    if(!spriteCount) return;

    if(sprites[spriteIndex]->good) sprites[spriteIndex]->Draw(renderer, x, y);

    ++spriteIndex;
    if(spriteIndex == spriteCount) spriteIndex = 0;
}

//* Pass -1 to w or h to keep the same value
//* Pass -1 to change all sprites
void MultiTexture::ChangeSize(int index, int w, int h){
    if(index == spriteCount) return;
    
    if(index == -1){
        for(int i = 0; i < spriteCount; ++i){
            sprites[i]->ChangeSize(w, h);
        }
    }
    else{
        sprites[index]->ChangeSize(w, h);
    }
}