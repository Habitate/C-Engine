#ifndef OBJ_PLAYER2
#define OBJ_PLAYER2

#include "Object.h"
#include "InputHandler.h"
#include "Texture.h"
#include <SDL2/SDL.h>

class Obj_player2 : public Object{
    public:
        Obj_player2(SDL_Renderer* renderer, SDL_Event* event);
        Obj_player2(SDL_Renderer* renderer, SDL_Event* event, const Texture& sprite);
        
        // Copyable
        Obj_player2(Obj_player2& object);
        Obj_player2& operator=(Obj_player2& object);

        // Moveable
        Obj_player2(Obj_player2&& object);
        Obj_player2& operator=(Obj_player2&& object);
        
        ~Obj_player2() override;

        void begin_step() override;
        void step()       override;
        void end_step()   override;

        SDL_Event* event;
        SDL_Renderer* renderer;
};

#endif // OBJECT_H2