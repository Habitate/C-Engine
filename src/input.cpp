#include "input.h"
#include <vector>

void InputHandler::syncStates(){
    std::copy(current_state, current_state + array_size, prev_state.data());
}

bool InputHandler::pressed(const SDL_Scancode scancode) noexcept{
    return !prev_state[scancode] && current_state[scancode];
}
bool InputHandler::released(const SDL_Scancode scancode) noexcept{
    return prev_state[scancode] && !current_state[scancode];
}
bool InputHandler::held(const SDL_Scancode scancode) noexcept{
    return current_state[scancode];
}

int                InputHandler::array_size;
const Uint8* const InputHandler::current_state(SDL_GetKeyboardState(&array_size));
std::vector<Uint8> InputHandler::prev_state(static_cast<unsigned int>(array_size));