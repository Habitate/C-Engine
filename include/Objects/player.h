#ifndef OBJ_PLAYER
#define OBJ_PLAYER

#include "Object.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>

class Obj_player : public Object{
    public:
        Obj_player(SDL_Renderer* renderer, SDL_Event* event);

        // Copyable
		Obj_player(Obj_player& obj);
		Obj_player& operator=(Obj_player& obj);

		// Moveable
		Obj_player(Obj_player&& obj);
		Obj_player& operator=(Obj_player&& obj);

        ~Obj_player();

        void draw(SDL_Renderer* const renderer);

        void begin_step() override;
        void step()       override;
        void end_step()   override;

        SDL_RendererFlip flip;
        SDL_Event* event;
};

#endif // OBJECT_H