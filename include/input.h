#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "gsl/span"

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
        static void init();

        //? Syncs the previous keyboard state with the current keyboard state
        static void syncStates();

        static bool pressed(const SDL_Scancode scancode) noexcept;
        static bool released(const SDL_Scancode scancode) noexcept;
        static bool held(const SDL_Scancode scancode) noexcept;

    private:
        static gsl::span<const Uint8> current_state;
        static std::vector<Uint8> prev_state;
};