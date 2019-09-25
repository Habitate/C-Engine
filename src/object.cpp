#include "object.h"

Object::Object(Game* const game) noexcept: sprite(), body{0, 0 , 0, 0}, camera(nullptr), game_ptr(game){}
Object::Object(Game* const game, Camera* const camera) noexcept: sprite(), body{0, 0, 0, 0}, camera(camera), game_ptr(game){}
Object::Object(Game* const game, const SDL_Rect& body, Camera* const camera) noexcept : sprite(), body(body), camera(camera), game_ptr(game){}

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
    sprite.draw(*camera, body.x, body.y);
}

bool Object::checkCollision(const Object& obj) const noexcept{
    return sprite[0].check_collision(obj.sprite[0]);   
}
