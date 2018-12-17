#ifndef OBJECT_H
#define OBJECT_H

#include "myInternet.h"
#include "Texture.h"

class Object
{
    public:
        Object();
        ~Object();

        void Initialize(int, int, bool);

        void Update(bool, SOCKET = 0);

        bool checkCollision(Object&);

        bool checkMoreCollision(Object&);

        Texture sprite;

        bool serverObject;
        int x;
        int y;
        int w;
        int h;
};

#endif // OBJECT_H