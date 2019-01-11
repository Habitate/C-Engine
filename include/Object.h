#ifndef OBJECT_H
#define OBJECT_H

#include "Texture.h"

class Object
{
    public:
        Object();
        Object(int x, int y, int w, int h);

        void Update();
        bool checkCollision(Object& object);

        Texture sprite;
        int x, y;
        int w, h;
};

#endif // OBJECT_H