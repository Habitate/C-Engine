#ifndef OBJECT_H
#define OBJECT_H

#include "Sprite.h"
#include <SDL2/SDL.h>
#include "camera.h"

class Game; // Forward declare

class Object{
    public:
        Object(Game* const game) noexcept;
        Object(Game* const game, Camera* const camera) noexcept;
        Object(Game* const game, const SDL_Rect& body, Camera* const camera) noexcept;
        
        // Copyable
        Object(Object& obj) noexcept;
		Object& operator=(Object& obj) noexcept;

		// Moveable
		Object(Object&& obj) noexcept;
		Object& operator=(Object&& obj) noexcept;

        virtual ~Object() noexcept;

        virtual void begin_step();
        virtual void step();
        virtual void end_step();

        void sync_sprite() const noexcept;

        virtual void draw() const;
        bool checkCollision(const Object& object) const noexcept;

        mutable Sprite sprite;
        SDL_Rect body;

        Camera* camera;

        Game* game_ptr;
};

#endif // OBJECT_H