#include "Functions.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <windows.h>
#include <thread>
#include <sys/stat.h> //* Used for file checking

#include "color.h"
#include <string>
#include <algorithm>

void sendPosition(int* x, int* y, SOCKET DataSocket){
    static char positions[5] = {0};

    *((short*)(positions + 0)) = *x;
    *((short*)(positions + 2)) = *y;

    send(DataSocket, positions, 5, 0);
}
void recievePosition(int* x, int* y, SOCKET DataSocket){
    static char positions[5] = {0};
    recv(DataSocket, positions, 5, 0);

    *x = *((short*)(positions + 0));
    *y = *((short*)(positions + 2));
}

bool fileExists(const std::string& path){
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

std::string getExtension(const std::string& path){
    std::string::const_reverse_iterator dot = std::find(path.rbegin(), path.rend(), '.');

    return dot == path.rend() ? std::string() : std::string(dot.base() - 1, path.end());
}