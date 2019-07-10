#include "Font.h"

#include <iostream>
#include <exception>
#include <memory>
#include "color.h"

Font::Font() noexcept: path(), size(0), font(nullptr, TTF_CloseFont) {}
Font::Font(const std::string& path, const unsigned int size) : path(path), size(size), font(TTF_OpenFont(path.c_str(), (int)size), TTF_CloseFont){
    if(!font){
        throw std::runtime_error((std::string("Failed to initialize font!\n\tFont path: ") + path + "\n\tsize: " + std::to_string(size) + "\n\tTTF Errors: " + TTF_GetError() + "!\n").c_str());
    }

    std::cout << Color(10) << "Successfully loaded font: \"" << Color(11) << path << Color(10) << "\"\n" << Color(7);
}

bool Font::good() const noexcept{
    return (bool)font;
}

void Font::set(const std::string& path, const unsigned int size){
    //? Prevent unnecessary reloading
    if(this->path == path && this->size == size){
        return;
    }

    this->path = path;
    this->size = size;
    update();

    std::cout << Color(10) << "Successfully loaded font: \"" << Color(11) << path << Color(10) << "\"\n" << Color(7);
}

void Font::setSize(const unsigned int size){
    //? Prevent unnecessary reloading
    if(this->size == size){
        return;
    }

    this->size = size;
    update();
}
void Font::setFont(const std::string& path){
    //? Prevent unnecessary reloading
    if(this->path == path){
        return;
    }

    this->path = path;
    update();

    std::cout << Color(10) << "Successfully loaded font: \"" << Color(11) << path << Color(10) << "\"\n" << Color(7);
}

const unsigned int& Font::getSize() const noexcept{
    return size;
}
const std::string& Font::getPath() const noexcept{
    return path;
}

void Font::update(){
    font.reset(TTF_OpenFont(path.c_str(), (int)size));

    if(!font){
        throw std::runtime_error((std::string("Failed to initialize font!\n\tFont path: ") + path + "\n\tsize: " + std::to_string(size) + "\n\tTTF Errors: " + TTF_GetError() + "!\n").c_str());
    }
}

void Font::draw_text(SDL_Renderer* const renderer, const std::string& text, const int x, const int y, const SDL_Color& color) const{
    if(!font){
        throw std::runtime_error((std::string("Failed to draw text " + text + "\n\tTTF Errors: " + TTF_GetError() + "!\n")).c_str());
    }

    const std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> loader(TTF_RenderText_Blended(this->font.get(), text.c_str(), color), SDL_FreeSurface);
    
    if(!loader){
        throw std::runtime_error((std::string("Failed to draw text " + text + "\n\tTTF Errors: " + TTF_GetError() + "!\n")).c_str());
    }

    const std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> sprite(SDL_CreateTextureFromSurface(renderer, loader.get()), SDL_DestroyTexture);

    if(!sprite){
        throw std::runtime_error((std::string("Failed to draw text " + text + "\n\tTTF Errors: " + TTF_GetError() + "!\n")).c_str());
    }
    
    const SDL_Rect srcRect = {0, 0, loader->w, loader->h};
    const SDL_Rect dstRect = {x, y, loader->w, loader->h};
    
    SDL_RenderCopy(renderer, sprite.get(), &srcRect, &dstRect);
}

std::shared_ptr<SDL_Texture> Font::render_text(SDL_Renderer* const renderer, const std::string& text, const SDL_Color& color) const{
    if(!font){
        throw std::runtime_error((std::string("Failed to render text " + text + "\n\tTTF Errors: " + TTF_GetError() + "!\n")).c_str());
    }

    const std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> loader(TTF_RenderText_Blended(this->font.get(), text.c_str(), color), SDL_FreeSurface);
    
    if(!loader){
        throw std::runtime_error((std::string("Failed to render text " + text + "\n\tTTF Errors: " + TTF_GetError() + "!\n")).c_str());
    }

    const std::shared_ptr<SDL_Texture> sprite(SDL_CreateTextureFromSurface(renderer, loader.get()), SDL_DestroyTexture);

    if(!sprite){
        throw std::runtime_error((std::string("Failed to render text " + text + "\n\tTTF Errors: " + TTF_GetError() + "!\n")).c_str());
    }
    
    return sprite;
}
