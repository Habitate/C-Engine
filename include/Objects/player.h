#ifndef OBJ_PLAYER
#define OBJ_PLAYER

#include "Object.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>

class Obj_player : public Object{
    public:
        Obj_player(SDL_Renderer* renderer, SDL_Event* event);

        // Copyable
        Obj_player(Obj_player& object);
        Obj_player& operator=(Obj_player& object);

        // Moveable
        Obj_player(Obj_player&& object);
        Obj_player& operator=(Obj_player&& object);

        ~Obj_player() override;

        void begin_step() override;
        void step()       override;
        void end_step()   override;

        SDL_Event* event;
        SDL_Renderer* renderer;
};

#endif // OBJECT_H