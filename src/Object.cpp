#include "Object.h"

#include "Functions.h"
#include "Texture.h"
#include <iostream>

void Object::begin_step(){}
void Object::step(){}
void Object::end_step(){}

Object::Object() : sprite(), body{0, 0 , 0, 0}{
}
Object::Object(const SDL_Rect& body) : sprite(), body(body){
}
Object::~Object(){
}

void Object::syncSprite(){
    sprite.getDstRect(0) = body;
}

void Object::draw(SDL_Renderer* renderer){
    sprite.draw(renderer, body.x, body.y);
}

bool Object::checkCollision(Object& obj){
    return SDL_HasIntersection(&this->sprite.getDstRect(0), &obj.sprite.getDstRect(0)) == SDL_TRUE;
}