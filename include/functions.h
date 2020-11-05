#pragma once

#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

bool file_exists(const std::string& path);

std::string get_extension(const std::string& path);

std::string operator+(const std::string& str, const void* ptr);

template<typename InputIt, typename T>
constexpr bool exists(InputIt first, InputIt last, const T& value){
    for(; first != last; ++first){
        if(*first == value) {
            return true;
        }
    }

    return false;
}