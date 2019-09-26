#pragma once

#include "Sprite.h"
#include <SDL2/SDL.h>

//? Forward declares
//? Declaring pointer types to minimize preprocessing (also can't include 'Game' any other way)
class Camera;
class Game;

class Object{
    public:
        explicit Object(Game* const game) noexcept;
        explicit Object(Game* const game, Camera* const camera) noexcept;
        explicit Object(Game* const game, const SDL_Rect& body, Camera* const camera) noexcept;
        
        // Copyable
        explicit Object(const Object& obj) noexcept;
		Object& operator=(const Object& obj) noexcept;

		// Moveable
		explicit Object(Object&& obj) noexcept;
		Object& operator=(Object&& obj) noexcept;

        virtual ~Object() noexcept;

        //*----------------------------------------------------

        virtual void begin_step();
        virtual void step();
        virtual void end_step();

        virtual void draw() const = 0;
        [[nodiscard]] bool checkCollision(const Object& object) const noexcept;

        mutable Sprite sprite;

        Camera* camera;
        Game*  game_ptr;
};
