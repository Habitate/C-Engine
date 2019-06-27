#ifndef OBJ_PLAYER
#define OBJ_PLAYER

#include "Object.h"

class Obj_player : public Object{
    public:
        Obj_player(SDL_Renderer* renderers);
        ~Obj_player();

        void begin_step() override;
        void step()       override;
        void end_step()   override;
};

#endif // OBJECT_H