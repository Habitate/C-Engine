#pragma once

#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>

[[nodiscard]] bool file_exists(const std::string& path) noexcept;

[[nodiscard]] std::string get_extension(const std::string& path);

[[nodiscard]] std::string operator+(const std::string& str, const void* ptr) noexcept;

//* Guarantees that the loaded texture is valid. Throws otherwise
[[nodiscard]] std::shared_ptr<SDL_Texture> load_texture(SDL_Renderer* const renderer, const std::string& path);

template<typename InputIt, typename T>
[[nodiscard]] constexpr bool exists(InputIt first, InputIt last, const T& value) noexcept{
    for(; first != last; ++first){
        if(*first == value) {
            return true;
        }
    }

    return false;
}