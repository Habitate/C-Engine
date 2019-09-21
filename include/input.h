#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>

class InputHandler{
    public:
        //? Syncs the current keyboard state with the previous keyboard state
        static void syncStates();

        static bool pressed(const SDL_Scancode scancode);
        static bool released(const SDL_Scancode scancode);
        static bool held(const SDL_Scancode scancode);

    private:
        static int array_size;
        static const Uint8* const current_state;
        static std::vector<Uint8> prev_state;
};