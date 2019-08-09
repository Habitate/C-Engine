#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

/// --- Internet --- ///
void sendPosition(int*, int*, SOCKET);
void recievePosition(int*, int*, SOCKET);

bool fileExists(const std::string& path);

std::string getExtension(const std::string& path);

#endif // FUNCTIONS_H