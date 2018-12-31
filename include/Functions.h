#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "myInternet.h"
#include <Windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/// --- Internet --- ///
void sendPosition(int*, int*, SOCKET);
void recievePosition(int*, int*, SOCKET);

// --- Misc --- ///
char* stringWInt(char*, const char*,int);

void color(int);

char getInput();

bool fileExists(std::string path);

// Loader functions

// TTF_RenderText_Blended
bool LoadSDLTexture(SDL_Renderer*, SDL_Surface**, SDL_Texture**, SDL_Surface* loaderFunction(TTF_Font*, const char*, SDL_Color), TTF_Font*, const char*, SDL_Color);

// IMG_Load
bool LoadSDLTexture(SDL_Renderer*, SDL_Surface**, SDL_Texture**, SDL_Surface* loaderFunction(const char*), const char*);

//? Both return false if the file does not contain an extension
bool getExtensionStart(std::string fileName, int& pos);
bool cutExtension(std::string& file, std::string& ext);

#endif // FUNCTIONS_H