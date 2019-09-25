#include "functions.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <windows.h>
#include <sys/stat.h> //* Used for file checking

#include "color.h"
#include <string>
#include <algorithm>

#include <sstream>

bool file_exists(const std::string& path){
    struct stat stats;

    return (stat(path.c_str(), &stats) == 0);
}

std::string get_extension(const std::string& path){
    std::string::const_reverse_iterator dot = std::find(path.rbegin(), path.rend(), '.');

    return dot == path.rend() ? std::string() : std::string(dot.base() - 1, path.end());
}

std::string operator+(const std::string& str, const void* ptr){
    std::stringstream stream;
    stream << ptr;

    return str + stream.str();
}
