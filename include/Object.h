#ifndef OBJECT_H
#define OBJECT_H

#include "Sprite.h"
#include <SDL2/SDL.h>

class Object{
    public:
        Object();
        Object(const SDL_Rect& body);
        virtual ~Object();

        // Copyable
        Object(Object& obj);
		Object& operator=(Object& obj);

		//Moveable
		Object(Object&& obj);
		Object& operator=(Object&& obj);

        virtual void begin_step();
        virtual void step();
        virtual void end_step();

        void syncSprite();

        virtual void draw(SDL_Renderer* const renderer);
        bool checkCollision(Object& object);

        Sprite sprite;
        SDL_Rect body;
};

#endif // OBJECT_H