#ifndef OBJECT_H
#define OBJECT_H

#include "Texture.h"

class Object
{
    public:
        Object();
        Object(const SDL_Rect& body);

        void Update();
        bool checkCollision(Object& object);

        Texture sprite;
        SDL_Rect body;
};

#endif // OBJECT_H