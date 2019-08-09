#include "sprite.h"

#include "functions.h"

Sprite::Sprite() noexcept : textures(), visable(true), sprite_index(0), animation_begin(0), animation_end(0), animating_once(false), animating(true){}
Sprite::Sprite(SDL_Renderer* renderer, const std::string& fileName) : Sprite(){
    load_single(renderer, fileName);
}
Sprite::Sprite(SDL_Renderer* renderer, const std::string& fileName, const std::string& extension) : Sprite(){
    load_multiple(renderer, fileName, extension);
}
Sprite::Sprite(SDL_Renderer* renderer, const std::string& fileName, const std::string& extension, unsigned int animation_begin, unsigned animation_end) : Sprite(renderer, fileName, extension){
    this->animation_begin = animation_begin;
    this->animation_end   = animation_end;
}

Sprite::Sprite(Sprite& obj) noexcept : textures(obj.textures.size()), visable(obj.visable), sprite_index(obj.sprite_index), animation_begin(obj.animation_begin), animation_end(obj.animation_end), animating_once(obj.animating_once), animating(obj.animating){
    const unsigned int textureCount = textures.size();

    for(unsigned int i = 0; i < textureCount; ++i){
        textures[i].reset(new Texture(*obj.textures[i]));
    }
}
Sprite& Sprite::operator=(Sprite& obj) noexcept{
    textures.resize(obj.textures.size());

    const unsigned int textureCount = textures.size();

    for(unsigned int i = 0; i < textureCount; ++i){
        textures[i].reset(new Texture(*obj.textures[i]));
    }

	animation_begin = obj.animation_begin;
	animation_end = obj.animation_end;
    animating_once = obj.animating_once;
	sprite_index = obj.sprite_index;
	animating = obj.animating;
    visable = obj.visable;

    return *this;
}

Sprite::Sprite(Sprite&& obj) noexcept = default;
Sprite& Sprite::operator=(Sprite&& obj) noexcept = default;

void Sprite::load_single(SDL_Renderer* renderer, const std::string& fileName){
    if(!textures.empty()){
        textures.clear();
    }

    //* Throws if necessary
    textures.emplace_back(new Texture(renderer, fileName));

    animation_begin = 0;
    animation_end = 0;
}
void Sprite::load_multiple(SDL_Renderer* renderer, const std::string& fileName, const std::string& extension){
    if(!textures.empty()){
        textures.clear();
    }

    std::string fullPath = fileName + '_' + std::to_string(textures.size()) + extension;

    do{
        //* Throws if necessary
        textures.emplace_back(new Texture(renderer, fullPath));

        fullPath = fileName + '_' + std::to_string(textures.size()) + extension;
    }while(fileExists(fullPath));

    animation_begin = 0;
    animation_end = textures.size() - 1;
}

unsigned int Sprite::count() const noexcept{
    return textures.size();
}

unsigned int Sprite::get_index() const noexcept{
    return sprite_index;
}
void Sprite::set_index(const unsigned int index){
    if(!valid_texture_selection(index)){
        throw std::runtime_error("Tried to the sprite index to an invalid value!");
    }

    sprite_index = index;
}

Texture& Sprite::operator[](const unsigned int index) noexcept{
    return *textures[index];
}
const Texture& Sprite::operator[](const unsigned int index) const noexcept{
    return *textures[index];
}

Texture& Sprite::at(const unsigned int index){
    if(!valid_texture_selection(index)){
        throw std::runtime_error("Tried to access a non-existant texture!");
    }

    return *textures[index];
}
const Texture& Sprite::at(const unsigned int index) const{
    if(!valid_texture_selection(index)){
        throw std::runtime_error("Tried to access a non-existant texture!");
    }

    return *textures[index];
}

void Sprite::draw_ext(SDL_Renderer* const renderer, const int x, const int y, const double& angle, const SDL_Point* const center, const SDL_RendererFlip& flip) const{
    //* Throws if necessary
    textures[sprite_index]->draw_ext(renderer, x, y, angle, center, flip);

    iterate();
}
void Sprite::draw_raw(SDL_Renderer* const renderer, const int x, const int y) const{
    //* Throws if necessary
    textures[sprite_index]->draw_raw(renderer, x, y);

    iterate();
}

void Sprite::set_dimensions(const int w, const int h) noexcept{
    for(std::unique_ptr<Texture>& texture : textures){
        texture->set_dimensions(w, h);
    }
}
void Sprite::set_width(const int width) noexcept{
    for(std::unique_ptr<Texture>& texture : textures){
        texture->set_width(width);
    }
}
void Sprite::set_height(const int height) noexcept{
    for(std::unique_ptr<Texture>& texture : textures){
        texture->set_height(height);
    }
}

void Sprite::reset_dimensions() noexcept{
    for(std::unique_ptr<Texture>& texture : textures){
        texture->reset_dimensions();
    }
}
void Sprite::reset_width() noexcept{
    for(std::unique_ptr<Texture>& texture : textures){
        texture->reset_width();
    }
}
void Sprite::reset_height() noexcept{
    for(std::unique_ptr<Texture>& texture : textures){
        texture->reset_height();
    }
}

void Sprite::iterate() const noexcept{
    if(!animating){
        return;
    }

    if(sprite_index != animation_end){
        sprite_index = sprite_index + 1 == textures.size() ? 0 : sprite_index + 1;
    }
    else{
       sprite_index = animation_begin; 

       if(animating_once){
           animating_once = false;
           animating = false;
       }
    }
}
void Sprite::animate_once() const noexcept{
    animating = true;
    animating_once = true;
}
void Sprite::animate_continuos() const noexcept{
    animating = true;
    animating_once = false;
}

void Sprite::stop_animating() const noexcept{
    animating = false;
    animating_once = false;
}
void Sprite::reset_animation() const noexcept{
    sprite_index = animation_begin;
}

void Sprite::set_animation_range(unsigned int beg, unsigned int end){
    if(!valid_texture_selection(beg) || !valid_texture_selection(end)){
        throw std::runtime_error("Tried to set the animation range to invalid values!");
    }

    animation_begin = beg;
    animation_end = end;
}
void Sprite::set_animation_begin(unsigned int beg){
    if(!valid_texture_selection(beg)){
        throw std::runtime_error("Tried to set the beggining of the animation range to an invalid value!");
    }

    animation_begin = beg;
}
void Sprite::set_animation_end(unsigned int end){
    if(!valid_texture_selection(end)){
        throw std::runtime_error("Tried to set the end of the animation range to an invalid value!");
    }

    animation_end = end;
}

bool Sprite::is_animating() const noexcept{
    return animating;
}
bool Sprite::is_animating_once() const noexcept{
    return animating_once;
}

bool Sprite::valid_texture_selection(const unsigned int pos) const noexcept{
    return pos < textures.size();
}

void Sprite::set_depth(unsigned int depth){
    at(0).set_depth(depth);
}
unsigned int Sprite::get_depth() const{
    return at(0).get_depth();
}