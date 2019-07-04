#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

/// --- Internet --- ///
void sendPosition(int*, int*, SOCKET);
void recievePosition(int*, int*, SOCKET);

// --- Misc --- ///
char* stringWInt(char*, const char*,int);

void color(int);

char getInput();
 
bool fileExists(std::string path);

// Loader functions

//? Both return false if the file does not contain an extension
bool getExtensionStart(std::string fileName, int& pos);
bool cutExtension(std::string& file, std::string& ext);

#endif // FUNCTIONS_H