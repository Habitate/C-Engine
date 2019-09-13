#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>

class InputHandler{
    public:
        static void Init();

        //? Syncs the current keyboard state with the class buffers
        static void syncStates();

        static bool pressed(const SDL_Scancode scancode);
        static bool released(const SDL_Scancode scancode);
        static bool held(const SDL_Scancode scancode);

    private:
        static const Uint8* currentState;
        static std::vector<Uint8> prevState;

        static unsigned int arraySize;
};