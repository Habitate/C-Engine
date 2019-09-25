#include "input.h"
#include <vector>

void InputHandler::init(){
    int size;
    const Uint8* data(SDL_GetKeyboardState(&size));

    current_state = gsl::span<const Uint8>(data, size);
    prev_state.resize(static_cast<unsigned int>(size));
}

void InputHandler::syncStates(){
    std::copy(std::begin(current_state), std::end(current_state), std::begin(prev_state));
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

gsl::span<const Uint8> InputHandler::current_state;
std::vector<Uint8> InputHandler::prev_state;