#include "input.h"
#include <cstring>
#include <vector>

unsigned int       InputHandler::arraySize;
const Uint8*       InputHandler::currentState;
std::vector<Uint8> InputHandler::prevState;

void InputHandler::Init(){
    currentState = SDL_GetKeyboardState((int*)&arraySize);
    prevState.resize(arraySize);
}

void InputHandler::syncStates(){
    memcpy(prevState.data(), currentState, arraySize);
}
bool InputHandler::pressed(SDL_Scancode scancode){
    return !prevState[scancode] && currentState[scancode];
}
bool InputHandler::released(SDL_Scancode scancode){
    return prevState[scancode] && !currentState[scancode];
}
bool InputHandler::held(SDL_Scancode scancode){
    return currentState[scancode];
}