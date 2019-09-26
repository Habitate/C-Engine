#include "obj/player.h"

#include <SDL2/SDL.h>
#include "input.h"
#include "camera.h"
#include "Game.h"
#include "sound.h"

#include <iostream>

Obj_player::Obj_player(Game* const game, SDL_Renderer* const renderer, Camera* const camera, SDL_Event* const event) : Object(game, camera), flip(SDL_FLIP_NONE), event(event), sound("../assets/sounds/test.wav"), pos{0,0}{
    sprite.load_multiple(renderer, "../assets/anim/test/test", ".png");

    sprite.set_index(35);
    sprite.set_animation_range(35, 34);
    sprite.stop_animating();

    pos = {100, game_ptr->HREZ - 64 - 100};
    sprite.set_width(100);
    sprite.set_height(100);
}

Obj_player::Obj_player(Obj_player& obj) = default;
Obj_player& Obj_player::operator=(Obj_player& obj) = default;

Obj_player::Obj_player(Obj_player&& obj) = default;
Obj_player& Obj_player::operator=(Obj_player&& obj) = default;

Obj_player::~Obj_player() = default;

void Obj_player::draw() const{
    sprite.draw(*camera, coords, 0, nullptr, flip);
}

void Obj_player::begin_step(){
    //
}
void Obj_player::step(){
    if(InputHandler::held(SDL_SCANCODE_A)){
        pos.x -= 3;
        flip = SDL_FLIP_NONE;
    }
    if(InputHandler::held(SDL_SCANCODE_D)){
        pos.x += 3;
        flip = SDL_FLIP_HORIZONTAL;
    }
    if(InputHandler::pressed(SDL_SCANCODE_W)){
        if(!sprite.is_animating()){
            sprite.animate_once();
        }
    }

    if(InputHandler::pressed(SDL_SCANCODE_X)){
        sound.play();
    }
    if(InputHandler::pressed(SDL_SCANCODE_Z)){
        sound.load("../assets/sounds/drift.mp3");
    }

    //? Movement
    if(InputHandler::held(SDL_SCANCODE_P)){
        sprite.set_width(sprite[0].get_dst_rect().w + 3);
        pos.y -= 3;
    }
    if(InputHandler::held(SDL_SCANCODE_O)){
        sprite.set_width(sprite[0].get_dst_rect().w - 3);
        pos.y += 3;
    }
    if(InputHandler::held(SDL_SCANCODE_L)){
        sprite.set_width(sprite[0].get_dst_rect().w + 3);
    }
    if(InputHandler::held(SDL_SCANCODE_K)){
        sprite.set_width(sprite[0].get_dst_rect().w - 3);
    }
    if(InputHandler::pressed(SDL_SCANCODE_R)){
        pos = {100, 316};
        sprite.set_width(100);
        sprite.set_height(100);
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