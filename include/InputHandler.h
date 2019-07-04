#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <vector>
#include <memory>

class InputHandler{
    public:
        static void Init();

        //? Makes the previous keyboard state to be equal to the current keyboard state
        static void syncStates();

        static bool pressed(SDL_Scancode scancode);
        static bool released(SDL_Scancode scancode);
        static bool held(SDL_Scancode scancode);

    private:
        static const Uint8* currentState;
        static std::vector<Uint8> prevState;

        static int arraySize;
};

#endif // INPUTHANDLER_H