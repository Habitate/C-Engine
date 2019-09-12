#include "obj/player.h"

#include <SDL2/SDL.h>
#include "input.h"
#include "camera.h"
#include "Game.h"

#include <iostream>

Obj_player::Obj_player(Game* const game, SDL_Renderer* const renderer, Camera* const camera, SDL_Event* const event) : Object(game, camera), flip(SDL_FLIP_NONE), event(event){
    sprite.load_multiple(renderer, "../assets/anim/test/test", ".png");

    sprite.set_index(35);
    sprite.set_animation_range(35, 34);
    sprite.stop_animating();

    //std::cout << game_ptr->HREZ;

    body = {100, game_ptr->HREZ - 64 - 100, 100, 100};
}

Obj_player::Obj_player(Obj_player& obj) = default;
Obj_player& Obj_player::operator=(Obj_player& obj) = default;

Obj_player::Obj_player(Obj_player&& obj) = default;
Obj_player& Obj_player::operator=(Obj_player&& obj) = default;

Obj_player::~Obj_player() = default;

void Obj_player::draw() const{
    sprite.draw(*camera, body.x, body.y, 0, nullptr, flip);
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

    //? Movement
    if(InputHandler::held(SDL_SCANCODE_P)){
        body.h += 3;
        body.y -= 3;
    }
    if(InputHandler::held(SDL_SCANCODE_O)){
        body.h -= 3;
        body.y += 3;
    }
    if(InputHandler::held(SDL_SCANCODE_L)){
        body.w += 3;
    }
    if(InputHandler::held(SDL_SCANCODE_K)){
        body.w -= 3;
    }
    if(InputHandler::pressed(SDL_SCANCODE_R)){
        body = {100, 316, 100, 100};
    }

    //? Camera
    if(InputHandler::held(SDL_SCANCODE_RIGHT)){
        camera->move_horizontal(2);
    }
    if(InputHandler::held(SDL_SCANCODE_LEFT)){
        camera->move_horizontal(-2);
    }
    if(InputHandler::held(SDL_SCANCODE_UP)){
        camera->move_vertical(-2);
    }
    if(InputHandler::held(SDL_SCANCODE_DOWN)){
        camera->move_vertical(2);
    }
    if(InputHandler::pressed(SDL_SCANCODE_M)){
        camera->zoom_in(0.1);
    }
    if(InputHandler::pressed(SDL_SCANCODE_N)){
        camera->zoom_out(0.1);
    }
}
void Obj_player::end_step(){
    sync_sprite();
} 