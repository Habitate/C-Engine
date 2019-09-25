#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>

class InputHandler{
    public:
        InputHandler() noexcept = delete;

        // Non-copyable
        InputHandler(const InputHandler&) noexcept = delete;
        InputHandler& operator=(const InputHandler&) noexcept = delete;

        // Non-moveable
        InputHandler(InputHandler&&) noexcept = delete;
        InputHandler& operator=(InputHandler&&) noexcept = delete;

        ~InputHandler() noexcept = delete;
        
        //*----------------------------------------------------

        //? Syncs the previous keyboard state with the current keyboard state
        static void syncStates();

        static bool pressed(const SDL_Scancode scancode) noexcept;
        static bool released(const SDL_Scancode scancode) noexcept;
        static bool held(const SDL_Scancode scancode) noexcept;

    private:
        static int array_size;
        static const Uint8* const current_state;
        static std::vector<Uint8> prev_state;
};