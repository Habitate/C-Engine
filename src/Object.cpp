#include "Object.h"

Object::Object() : sprite(), body{0, 0 , 0, 0}{
}
Object::Object(const SDL_Rect& body) : sprite(), body(body){
}
Object::~Object() = default;

Object::Object(Object& obj) = default;
Object& Object::operator=(Object& obj) = default;

Object::Object(Object&& obj) = default;
Object& Object::operator=(Object&& obj) = default;

void Object::begin_step(){}
void Object::step(){}
void Object::end_step(){}

void Object::syncSprite(){
    sprite.set_dimensions(body.w, body.h);
}

void Object::draw(SDL_Renderer* renderer){
    sprite.draw_raw(renderer, body.x, body.y);
}

bool Object::checkCollision(Object& obj){
    return sprite[0].check_collision(obj.sprite[0]);   
}