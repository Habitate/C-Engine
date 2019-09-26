#include "object.h"

Object::Object(Game* const game) noexcept: sprite(), camera(nullptr), game_ptr(game){}
Object::Object(Game* const game, Camera* const camera) noexcept: sprite(), body{0, 0, 0, 0}, camera(camera), game_ptr(game){}
Object::Object(Game* const game, const SDL_Rect& body, Camera* const camera) noexcept : sprite(), body(body), camera(camera), game_ptr(game){}

// Copyable
Object::Object(const Object& obj) noexcept = default;
Object& Object::operator=(const Object& obj) noexcept = default;

// Moveable
Object::Object(Object&& obj) noexcept = default;
Object& Object::operator=(Object&& obj) noexcept = default;

Object::~Object() noexcept = default;

//*----------------------------------------------------

void Object::begin_step(){}
void Object::step(){}
void Object::end_step(){}

bool Object::checkCollision(const Object& obj) const noexcept{
    return sprite[0].check_collision(obj.sprite[0]);   
}
