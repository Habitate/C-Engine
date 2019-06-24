#include "Object.h"

#include "Functions.h"
#include "Texture.h"

Object::Object() : body{0, 0 , 0, 0} {}
Object::Object(const SDL_Rect& body) : body(body) {}

void Object::Update(){
    // Sync the sprite
    sprite.getDstRect() = body;
}

bool Object::checkCollision(Object& obj){
    return SDL_HasIntersection(&this->sprite.getDstRect(), &obj.sprite.getDstRect()) == SDL_TRUE;
}