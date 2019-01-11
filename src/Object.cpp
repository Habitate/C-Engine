#include "Object.h"

#include "Functions.h"
#include "Texture.h"

Object::Object() : x(0), y(0), w(0), h(0) {}
Object::Object(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

void Object::Update(){
    // Sync the sprite
    sprite.GetRect(true).x = x;
    sprite.GetRect(true).y = y;
    w = sprite.GetRect(true).w;
    h = sprite.GetRect(true).h;
}

bool Object::checkCollision(Object& obj){
    if(SDL_TRUE != SDL_HasIntersection(&this->sprite.GetRect(false), &obj.sprite.GetRect(true))) return true;
    return false;
}