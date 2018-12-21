#include "Object.h"

#include "myInternet.h"
#include "Functions.h"
#include "Texture.h"

Object::Object(){
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->serverObject = false;
}
Object::~Object(){
    // Something
}

void Object::Initialize(int x, int y, bool serverObject){
    // Construct
    Object();

    // Initialize
    this->x = x;
    this->y = y;
    this->serverObject = serverObject;
}

void Object::Update(bool connectedToServer, SOCKET DataSocket){
    // Sync the sprite
    sprite.dstRect.x = x;
    sprite.dstRect.y = y;
    w = sprite.dstRect.w;
    h = sprite.dstRect.h;

    // Update animations

    // Send over your position
    if(connectedToServer && !serverObject) sendPosition(&x, &y, DataSocket);
    if(connectedToServer && serverObject ) recievePosition(&x, &y, DataSocket);
}

bool Object::checkCollision(Object& obj){
    return (abs(x - obj.x) * 2 < (w + obj.w )) && (abs(y - obj.y) * 2 < (h + obj.h));
}

bool Object::checkMoreCollision(Object& obj){
    if(SDL_TRUE != SDL_HasIntersection(&this->sprite.dstRect, &obj.sprite.dstRect)) return true;
    return false;
}