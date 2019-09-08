#include "object.h"

Object::Object() noexcept : sprite(), body{0, 0 , 0, 0}{}
Object::Object(const SDL_Rect& body) noexcept : sprite(), body(body){}

Object::Object(Object& obj) noexcept = default;
Object& Object::operator=(Object& obj) noexcept = default;

Object::Object(Object&& obj) noexcept = default;
Object& Object::operator=(Object&& obj) noexcept = default;

Object::~Object() noexcept = default;

void Object::begin_step(){}
void Object::step(){}
void Object::end_step(){}

void Object::sync_sprite() const noexcept{
    sprite.set_dimensions(body.w, body.h);
}

void Object::draw() const{
    sprite.draw(body.x, body.y);
}

bool Object::checkCollision(const Object& obj) const noexcept{
    return sprite[0].check_collision(obj.sprite[0]);   
}