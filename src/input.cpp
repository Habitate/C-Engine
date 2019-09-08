#include "input.h"
#include <cstring>
#include <vector>

void InputHandler::Init(){
    currentState = SDL_GetKeyboardState((int*)&arraySize);
    prevState.resize(arraySize);
}

void InputHandler::syncStates(){
    memcpy(prevState.data(), currentState, arraySize);
}
bool InputHandler::pressed(const SDL_Scancode scancode){
    return !prevState[scancode] && currentState[scancode];
}
bool InputHandler::released(const SDL_Scancode scancode){
    return prevState[scancode] && !currentState[scancode];
}
bool InputHandler::held(const SDL_Scancode scancode){
    return currentState[scancode];
}

unsigned int       InputHandler::arraySize;
const Uint8*       InputHandler::currentState;
std::vector<Uint8> InputHandler::prevState;