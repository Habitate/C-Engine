#include "Objects/player2.h"
#include "Functions.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "InputHandler.h"

Obj_player2::Obj_player2(SDL_Renderer* renderer, SDL_Event* event) : event(event), renderer(renderer){
    sprite.load(renderer, "../assets/anim/test/test");
    sprite.setSize(0, 100, 100, true);
    body = sprite.getDstRect(0);

    body.x = 500;
    body.y = 316;
    
    sprite.setIndex(34);
    sprite.animationStartIndex = 34;
    sprite.animating = false;

    sprite.flip = SDL_FLIP_NONE;
    sprite.center = {sprite.getDstRect(0).w / 2, sprite.getDstRect(0).h / 2};
    sprite.angle = 0;
}
Obj_player2::Obj_player2(SDL_Renderer* renderer, SDL_Event* event, const Texture& sprite) : event(event), renderer(renderer){
    this->sprite = sprite;

    body = this->sprite.getDstRect(0);

    body.x = 500;
    body.y = 316;
}

Obj_player2::Obj_player2(Obj_player2& object) = default;
Obj_player2& Obj_player2::operator=(Obj_player2& object) = default;

Obj_player2::Obj_player2(Obj_player2&& object) = default;
Obj_player2& Obj_player2::operator=(Obj_player2&& object) = default;

Obj_player2::~Obj_player2(){
    //
}

void Obj_player2::begin_step(){
    //
}
void Obj_player2::step(){
    if(InputHandler::held(SDL_SCANCODE_LEFT)){
        body.x -= 3;
        sprite.flip = SDL_FLIP_NONE;
    }
    if(InputHandler::held(SDL_SCANCODE_RIGHT)){
        body.x += 3;
        sprite.flip = SDL_FLIP_HORIZONTAL;
    }

    if(InputHandler::pressed(SDL_SCANCODE_UP)){
        if(!sprite.animatingOnce){
            sprite.runAnimationOnce();
        }
    }

}
void Obj_player2::end_step(){
    syncSprite();
}