#include "Objects/player.h"
#include <iostream>

Obj_player::Obj_player(SDL_Renderer* renderer){
    sprite.load(renderer, "../assets/anim/test/test");
    sprite.setSize(-1, 100, 100);
    body = sprite.getDstRect();

    body.x = 320;
    body.y = 316;
    
    sprite.setIndex(34);
    sprite.animationStartIndex = 34;
    sprite.animating = false;
}
Obj_player::~Obj_player(){
    
}

void Obj_player::begin_step(){
    //
}
void Obj_player::step(){
    //
}
void Obj_player::end_step(){
    //
}