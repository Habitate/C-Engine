#include "Objects/player.h"
#include "Functions.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "InputHandler.h"

Obj_player::Obj_player(SDL_Renderer* renderer, SDL_Event* event) : renderer(renderer), event(event){
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
    //
}

void Obj_player::begin_step(){
    //
}
void Obj_player::step(){
    if(InputHandler::held(SDL_SCANCODE_A)){
        body.x -= 3;
    }
    if(InputHandler::held(SDL_SCANCODE_D)){
        body.x += 3;
    }

    if(InputHandler::pressed(SDL_SCANCODE_W)){
        if(!sprite.animatingOnce){
            sprite.runAnimationOnce();
        }
    }
}
void Obj_player::end_step(){
    syncSprite();
}