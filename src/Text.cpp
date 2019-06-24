// *********************************************************
//! Be sure to run TTF_Init() before using!
// *********************************************************

#include "Text.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <windows.h>
#include <stdio.h>

Text::Text(){
    loaderFunction = TTF_RenderText_Blended;
    
    good      = false;
    visable   = true;
    numerical = false;

    renderer = NULL;
    sprite   = NULL;
    number   = NULL;
    font     = NULL;

    oldNumber = 0;

    fontSize  = DEFAULTFONTSIZE;
    textColor = DEFAULTFONTCOLOR;

    strcpy(this->fontPath, DEFAULTFONT);
    strcpy(this->text, "");
 
    ZeroMemory(&srcRect, sizeof(srcRect));
    ZeroMemory(&dstRect, sizeof(srcRect));         
}
Text::Text(const Text& passedObject){
    strcpy(this->text, passedObject.text);
    strcpy(this->fontPath, passedObject.fontPath);

    this->loaderFunction = passedObject.loaderFunction;
    this->numerical      = passedObject.numerical;
    this->textColor      = passedObject.textColor;
    this->oldNumber      = passedObject.oldNumber;
    this->fontSize       = passedObject.fontSize;   
    this->renderer       = passedObject.renderer;
    this->srcRect        = passedObject.srcRect;
    this->dstRect        = passedObject.dstRect;
    this->visable        = passedObject.visable;
    this->number         = passedObject.number;
    this->good           = passedObject.good;
    this->font           = TTF_OpenFont(this->fontPath, this->fontSize);
    Load();              // Sets the sprite
}
Text::~Text(){
    SDL_DestroyTexture(this->sprite);
    TTF_CloseFont(this->font);
}
Text& Text::operator=(const Text& passedObject){
    strcpy(this->text, passedObject.text);
    strcpy(this->fontPath, passedObject.fontPath);

    this->loaderFunction = passedObject.loaderFunction;
    this->numerical      = passedObject.numerical;
    this->textColor      = passedObject.textColor;
    this->oldNumber      = passedObject.oldNumber;
    this->fontSize       = passedObject.fontSize;
    this->renderer       = passedObject.renderer;
    this->srcRect        = passedObject.srcRect;
    this->dstRect        = passedObject.dstRect;
    this->visable        = passedObject.visable;
    this->number         = passedObject.number;
    this->good           = passedObject.good;
    this->font           = TTF_OpenFont(this->fontPath, this->fontSize);
    Load();              // Sets the sprite

    return *this;
}
Text& Text::operator=(const char* text){
    ChangeText(text);

    return *this;
}

// Functionality functions
void Text::Initialize(SDL_Renderer* renderer, const char* text, const char* fontPath, int fontSize, SDL_Color textColor, int x, int y, bool numerical, int* number = NULL){
    strcpy(this->fontPath, fontPath);
    strcpy(this->text, text);

    this->renderer  = renderer;
    this->fontSize  = fontSize;
    this->textColor = textColor;
    this->numerical = numerical;
    this->number    = number;
    this->dstRect.x = x;
    this->dstRect.y = y;
    this->font      = TTF_OpenFont(this->fontPath, this->fontSize);

    this->good      = true;
    Load();
}
void Text::Initialize(SDL_Renderer* renderer, const char* text, int x, int y){
    strcpy(this->text, text);

    this->renderer  = renderer;
    this->dstRect.x = x;
    this->dstRect.y = y;
    this->font      = TTF_OpenFont(this->fontPath, this->fontSize);

    this->good      = true;
    Load();
}
void Text::Draw(){
    if(visable && good) SDL_RenderCopy(renderer, sprite, &srcRect, &dstRect);
}
void Text::Load(){
    if(sprite     != NULL) SDL_DestroyTexture(sprite);
    if(this->font == NULL) return;

    SDL_Surface* loader = loaderFunction(this->font, this->text, this->textColor);
    sprite              = SDL_CreateTextureFromSurface(this->renderer, loader);

    srcRect.w = loader->w;
    srcRect.h = loader->h;
    dstRect.w = loader->w;
    dstRect.h = loader->h;

    SDL_FreeSurface(loader);
}
void Text::Update(){
    if(!numerical || oldNumber == *number) return;
    if(sprite != NULL) SDL_DestroyTexture(sprite);

    // Create a temporary string
    static char temp[TEXTSIZE];
    strcpy(temp, this->text);
    sprintf(temp, "%s%d", temp, *number);

    SDL_Surface* loader = loaderFunction(this->font, temp, this->textColor);
    sprite              = SDL_CreateTextureFromSurface(this->renderer, loader);

    //Resize the text
    srcRect.w = loader->w;
    dstRect.w = loader->w;
    srcRect.h = loader->h;
    dstRect.h = loader->h;
            
    oldNumber = *number;
    SDL_FreeSurface(loader);
}

// Manipulation functions       
void Text::ChangeText(const char* text){
    if(!strcmp(this->text, text)) return;
    strcpy(this->text, text);

    // Reload the sprite
    Load();
}      
void Text::ChangeTextColor(SDL_Color textColor){
    this->textColor = textColor;

    // Reload the sprite
    Load();
}
void Text::ChangeFont(const char* fontPath){
    if(!strcmp(this->fontPath, fontPath)) return;
    strcpy(this->fontPath, fontPath);

    if(this->font != NULL) TTF_CloseFont(font);

    // Load the new font
    font = TTF_OpenFont(this->fontPath, this->fontSize);

    // Reload the sprite
    Load();
}
void Text::ChangeFontSize(int fontSize){
    if(this->fontSize == fontSize) return;
    if(this->font != NULL) TTF_CloseFont(font);

    this->fontSize = fontSize;

    // Load the new font
    font = TTF_OpenFont(this->fontPath, this->fontSize);            

    // Reload the sprite
    Load();
}
void Text::ChangeRenderer(SDL_Renderer* renderer){
    this->renderer = renderer;
}
void Text::ChangeVisability(bool visable){
    this->visable = visable;
}
void Text::ChangeLoaderFunction(SDL_Surface* (*loaderFunction)(TTF_Font*, const char*, SDL_Color)){
    this->loaderFunction = loaderFunction;
}
void Text::ChangeNumber(int* number){
    this->number = number;
}
void Text::SetNumericality(bool numerical){
    this->numerical = numerical;
}
void Text::SetX(int x){
    this->dstRect.x = x;
}
void Text::SetY(int y){
    this->dstRect.y = y;
}