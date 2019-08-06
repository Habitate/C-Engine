#include "Font.h"

#include <iostream>
#include <exception>
#include <memory>
#include "color.h"

Font::Font() noexcept: path(), size(0), font(nullptr, TTF_CloseFont) {}
Font::Font(const std::string& path, const unsigned int size) : path(), size(0), font(nullptr, TTF_CloseFont){
    load(path, size);
}

bool Font::good() const noexcept{
    return (bool)font;
}

void Font::load(const std::string& path, const unsigned int size){
    //? Prevent unnecessary reloading
    if(this->path == path && this->size == size){
        return;
    }

    this->path = path;
    this->size = size;
    update();
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
}

unsigned int Font::getSize() const noexcept{
    return size;
}
const std::string& Font::getPath() const noexcept{
    return path;
}

void Font::update(){
    font.reset(TTF_OpenFont(path.c_str(), (int)size));

    if(!font){
        std::cout << C(C::RED) << "Failed loading font: " << C(C::CYAN) << '\"'<< path << "\"\n" << C();
        std::cout << "\tError: " << SDL_GetError() << '\n';

        throw std::runtime_error("^^^");
    }
    else{
        std::cout << C(C::GREEN) << "Successfully loaded font: " << C(C::CYAN) << "\"" << path << "\"\n" << C();
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
