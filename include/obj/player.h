#pragma once

#include "object.h"
#include "input.h"
#include <SDL2/SDL.h>
#include "sound.h"

class Obj_player : public Object{
    public:
        explicit Obj_player(Game* const game, SDL_Renderer* const renderer, Camera* const camera, SDL_Event* const event);

        // Copyable
		explicit Obj_player(Obj_player& obj);
		Obj_player& operator=(Obj_player& obj);

		// Moveable
		explicit Obj_player(Obj_player&& obj);
		Obj_player& operator=(Obj_player&& obj);

        ~Obj_player();

        //**********************************************

        void draw() const override;

        void begin_step() override;
        void step() override;
        void end_step() override;

        SDL_RendererFlip flip;
        SDL_Event* event;

        Sound sound;
};