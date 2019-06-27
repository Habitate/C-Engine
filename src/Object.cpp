#include "Object.h"

#include "Functions.h"
#include "Texture.h"
#include <iostream>

void Object::begin_step(){}
void Object::step(){}
void Object::end_step(){}

Object::Object() : body{0, 0 , 0, 0}{
}
Object::Object(const SDL_Rect& body) : body(body){
}
Object::~Object(){
}

void Object::update(){
    // Sync the sprite
    sprite.getDstRect() = body;
}

void Object::draw(SDL_Renderer* renderer){
    sprite.draw(renderer, body.x, body.y);
}

bool Object::checkCollision(Object& obj){
    return SDL_HasIntersection(&this->sprite.getDstRect(), &obj.sprite.getDstRect()) == SDL_TRUE;
}