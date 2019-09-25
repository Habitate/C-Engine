#include "font.h"

#include <iostream>
#include <exception>
#include <memory>
#include "color.h"

Font::Font() noexcept: path(), size(0), font(nullptr, TTF_CloseFont) {}
Font::Font(const std::string& path, const unsigned int size) : Font(){
    load(path, size);
}

// Moveable
Font::Font(Font&& font) noexcept = default;
Font& Font::operator=(Font&& font) noexcept = default;

Font::~Font() noexcept = default;

//*----------------------------------------------------

void Font::load(const std::string& path, const unsigned int size){
    //? Prevent unnecessary loading
    if(this->path == path && this->size == size){
        return;
    }

    this->path = path;
    this->size = size;
    
    font.reset(TTF_OpenFont(path.c_str(), (int)size));

    if(!font){
        std::cout << C(C::RED) << "Failed loading font: " << C(C::CYAN) << '\"'<< path << "\"\n" << C();
        std::cout << "\tError: " << SDL_GetError() << '\n';

        throw std::runtime_error("");
    }
    else{
        std::cout << C(C::GREEN) << "Successfully loaded font: " << C(C::CYAN) << "\"" << path << "\"\n" << C();
    }
}
void Font::set_size(const unsigned int size){
    load(this->path, size);
}
void Font::set_font(const std::string& path){
    load(path, this->size);
}

unsigned int Font::get_size() const noexcept{
    return size;
}
const std::string& Font::get_path() const noexcept{
    return path;
}

void Font::draw_text(SDL_Renderer* const renderer, const std::string& text, const int x, const int y, const SDL_Color& color) const{
    if(!font){
        throw std::runtime_error("Tried to draw text from an uninitialized font!\n");
    }

    const std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> loader(TTF_RenderText_Blended(this->font.get(), text.c_str(), color), SDL_FreeSurface);
    if(!loader){
        throw std::runtime_error(std::string("TTF_RenderText_Blended failed when drawing text!\n\t   Error: ") + SDL_GetError() + '\n');
    }

    const std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> sprite(SDL_CreateTextureFromSurface(renderer, loader.get()), SDL_DestroyTexture);
    if(!sprite){
        throw std::runtime_error(std::string("SDL_CreateTextureFromSurface failed when drawing text!\n\t   Error: ") + SDL_GetError() + '\n');
    }
    
    const SDL_Rect srcRect = {0, 0, loader->w, loader->h};
    const SDL_Rect dstRect = {x, y, loader->w, loader->h};
    
    SDL_RenderCopy(renderer, sprite.get(), &srcRect, &dstRect);
}
std::shared_ptr<SDL_Texture> Font::render_text(SDL_Renderer* const renderer, const std::string& text, const SDL_Color& color) const{
    if(!font){
        throw std::runtime_error("Tried to draw text from an uninitialized font!\n");
    }

    const std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> loader(TTF_RenderText_Blended(this->font.get(), text.c_str(), color), SDL_FreeSurface);
    if(!loader){
        throw std::runtime_error(std::string("TTF_RenderText_Blended failed when rendering text!\n\t   Error: ") + SDL_GetError() + '\n');
    }

    const std::shared_ptr<SDL_Texture> sprite(SDL_CreateTextureFromSurface(renderer, loader.get()), SDL_DestroyTexture);
    if(!sprite){
        throw std::runtime_error(std::string("SDL_CreateTextureFromSurface failed when rendering text!\n\t   Error: ") + SDL_GetError() + '\n');
    }
    
    return sprite;
}

bool Font::good() const noexcept{
    return (bool)font;
}