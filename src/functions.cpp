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
#include <iostream>
#include "constants.h"

bool file_exists(const std::string& path) noexcept{
    struct stat stats;

    return !stat(path.c_str(), &stats);
}

std::string get_extension(const std::string& path){
    std::string::const_reverse_iterator dot = std::find(path.rbegin(), path.rend(), '.');

    return dot == path.rend() ? std::string() : std::string(dot.base() - 1, path.end());
}

std::string operator+(const std::string& str, const void* ptr) noexcept{
    std::stringstream stream;
    stream << ptr;

    return str + stream.str();
}

std::shared_ptr<SDL_Texture> load_texture(SDL_Renderer* const renderer, const std::string& path){
    std::shared_ptr<SDL_Texture> texture(IMG_LoadTexture(renderer, path.c_str()), SDL_DestroyTexture);

	if(!texture){
		std::cout << C(C::RED) << "Failed to load image: " << C(C::YELLOW) << path << "\"\n" << C();
		std::string error_msg;

		if(!file_exists(path)){
			error_msg += "File doesn't exist!\n";
		}

		if(!exists(std::begin(Texture_Constants::SUPPORTED_DATA_TYPES), std::end(Texture_Constants::SUPPORTED_DATA_TYPES), get_extension(path))){
			error_msg += "\t   No valid extension found!\n";
		}

        throw std::runtime_error(error_msg);
	}
	else{
		std::cout << C(C::GREEN) << "Successfully loaded image: " << C(C::YELLOW) << "\"" << path << "\"\n" << C();
	}

    return texture;
}