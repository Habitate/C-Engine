#ifndef OBJ_PLAYER
#define OBJ_PLAYER

#include "object.h"
#include "input.h"
#include <SDL2/SDL.h>

class Obj_player : public Object{
    public:
        Obj_player(SDL_Renderer* const renderer, SDL_Event* const event);

        // Copyable
		Obj_player(Obj_player& obj);
		Obj_player& operator=(Obj_player& obj);

		// Moveable
		Obj_player(Obj_player&& obj);
		Obj_player& operator=(Obj_player&& obj);

        ~Obj_player();

        void draw() const;

        void begin_step() override;
        void step() override;
        void end_step() override;

        SDL_RendererFlip flip;
        SDL_Event* event;
};

#endif // OBJECT_H