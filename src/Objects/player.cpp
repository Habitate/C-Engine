#include "Objects/player.h"

#include <SDL2/SDL.h>
#include "InputHandler.h"

Obj_player::Obj_player(SDL_Renderer* renderer, SDL_Event* event) : flip(SDL_FLIP_NONE), event(event){
    sprite.load_multiple(renderer, "../assets/anim/test/test", ".png");

    sprite.set_index(35);
    sprite.set_animation_range(35, 34);
    sprite.stop_animating();

    body = {100, 316, 100, 100};
}

Obj_player::Obj_player(Obj_player& obj) = default;
Obj_player& Obj_player::operator=(Obj_player& obj) = default;

Obj_player::Obj_player(Obj_player&& obj) = default;
Obj_player& Obj_player::operator=(Obj_player&& obj) = default;

Obj_player::~Obj_player() = default;

void Obj_player::draw(SDL_Renderer* const renderer){
    sprite.draw_ext(renderer, body.x, body.y, 0, nullptr, flip);
}

void Obj_player::begin_step(){
    //
}
void Obj_player::step(){
    if(InputHandler::held(SDL_SCANCODE_A)){
        body.x -= 3;
        flip = SDL_FLIP_NONE;
    }
    if(InputHandler::held(SDL_SCANCODE_D)){
        body.x += 3;
        flip = SDL_FLIP_HORIZONTAL;
    }

    if(InputHandler::pressed(SDL_SCANCODE_W)){
        if(!sprite.is_animating()){
            sprite.animate_once();
        }
    }

    if(InputHandler::held(SDL_SCANCODE_UP)){
        body.h += 3;
        body.y -= 3;
    }
    if(InputHandler::held(SDL_SCANCODE_DOWN)){
        body.h -= 3;
        body.y += 3;
    }
    if(InputHandler::held(SDL_SCANCODE_RIGHT)){
        body.w += 3;
    }
    if(InputHandler::held(SDL_SCANCODE_LEFT)){
        body.w -= 3;
    }
    if(InputHandler::pressed(SDL_SCANCODE_R)){
        body = {100, 316, 100, 100};
    }
}
void Obj_player::end_step(){
    syncSprite();
} 