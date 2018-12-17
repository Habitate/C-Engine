#include "Texture.h"

#include "Functions.h"
#include <iostream>
#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "color.h"

using namespace std;

Texture::Texture(){
    sprite = (SDL_Texture**)malloc(sizeof(SDL_Texture*));

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 0;
    srcRect.h = 0;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = 0;
    dstRect.h = 0;

    good = false;
    animateable = false;
    visable = true;
    animator = 0;
    animations = 0;
    animateOnce = false;
}

Texture::~Texture(){
    good = false;
}

void Texture::Initialize(){
    sprite = (SDL_Texture**)malloc(sizeof(SDL_Texture*));

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 0;
    srcRect.h = 0;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = 0;
    dstRect.h = 0;

    good = false;
    animateable = false;
    visable = true;
    animator = 0;
    animations = 0;
    animateOnce = false;
}

void Texture::startAnimation(bool once = false){
    animateOnce = once;

    animateable = true;
    animator   = 0;
}

void Texture::stopAnimation(){
    animateable = false;
}

void Texture::updateAnimation(){
    if(animateOnce && animator == animations && animateable){
        animateOnce = false;
        stopAnimation();
    }

    if(animator == animations && animateable) animator = 0;
    else animator++;
}

void Texture::errorCheck(SDL_Surface* loader, SDL_Texture** sprite, char* path, int num = 0){
    if(loader == NULL || sprite[num] == NULL){
            cout << Color(12) << "Failed loading: " << Color(7) << path << endl;
            good = false;
            return;
    }
            
    cout << Color(10) << "Successfully loaded: " << Color(7) << path << endl;
    good = true;
}

void Texture::loadAsMultiple(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h){
    char fileName[100] = {0};
    animateable        = true;

    // Get file count
    while(true){
        sprintf(fileName, "%s_%d.png", path, animations);

        if(!fileExists(fileName)){
            animations--;
            break;
        } animations++;   
    }
            
    cout << "Found " << Color(13) << animations + 1 << Color(7) << " animations for \"" << Color(14) << path << Color(7) << '\"';

    // Allocate the texture array
    sprite = (SDL_Texture**)malloc(sizeof(SDL_Texture*)*(animations + 1));

    // Load the textures
    for(int i = 0; i <= animations; i++){
        sprintf(fileName, "%s_%d.png", path, i);

        cout << '\t';
        SDL_Surface* loader;
        good = LoadSDLTexture(renderer, &loader, &sprite[i], IMG_Load, fileName);

        // Set the rectangle values
        srcRect.w = loader->w;
        srcRect.h = loader->h;
        dstRect.x = x;
        dstRect.y = y;
        dstRect.w = w;
        dstRect.h = h;

        // If w and h are 0, use loaded values
        if(w == 0 || h == 0){
            dstRect.w = loader->w;
            dstRect.h = loader->h;
        }

        // Free surface
        SDL_FreeSurface(loader);
    }
}

void Texture::loadAsSingle(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h){
    SDL_Surface* loader;
    good = LoadSDLTexture(renderer, &loader, &sprite[0], IMG_Load, path);

    // Set the rectangle values
    srcRect.w = loader->w;
    srcRect.h = loader->h;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;

    // If w and h are 0, use loaded values
    if(w == 0 || h == 0){
        dstRect.w = loader->w;
        dstRect.h = loader->h;
    }

    // Free surface
    SDL_FreeSurface(loader);
}

void Texture::draw(SDL_Renderer* renderer){
    // Error check 
    if(!good){
        cout << endl << "Can't draw an uninitialized texture!" << endl << endl;
        system("pause");

        return;
    }

    if(visable){
        // Decide on animations
        if(!animateable)
            SDL_RenderCopy(renderer, sprite[0], &srcRect, &dstRect);
            
        else{
            SDL_RenderCopy(renderer, sprite[animator], &srcRect, &dstRect);
        }
    }
}