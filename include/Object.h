#ifndef OBJECT_H
#define OBJECT_H

#include "Sprite.h"
#include <SDL2/SDL.h>

class Object{
    public:
        Object() noexcept;
        Object(const SDL_Rect& body) noexcept;
        
        // Copyable
        Object(Object& obj) noexcept;
		Object& operator=(Object& obj) noexcept;

		//Moveable
		Object(Object&& obj) noexcept;
		Object& operator=(Object&& obj) noexcept;

        virtual ~Object() noexcept;

        virtual void begin_step();
        virtual void step();
        virtual void end_step();

        void syncSprite() const noexcept;

        virtual void draw(SDL_Renderer* const renderer) const;
        bool checkCollision(const Object& object) const noexcept;

        mutable Sprite sprite;
        SDL_Rect body;
};

#endif // OBJECT_H