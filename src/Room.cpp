#include "Room.h"

#include "myInternet.h"
#include <SDL2/SDL.h>
#include <windows.h>
#include <iostream>
#include "Texture.h"
#include "Object.h"

Room::Room(){
    // Initialize objects, textures and texts
    objects  = (Object* )malloc(0);
    textures = (Texture*)malloc(sizeof(Texture));
    texts    = (Texture*)malloc(sizeof(Texture));
    objectCount  = 0;
    textureCount = 0;
    textCount    = 0;
}

Room::~Room(){
    // Something
}

void Room::Initialize(SDL_Window* window, SDL_Renderer* renderer){
    // Set the window and renderers
    this->window = window;
    this->renderer = renderer;
}

void Room::CreateObject(int x, int y, int w, int h, const char* path, bool multiple, bool serverObject){
    objects = (Object*)realloc(objects, sizeof(Object));
    if(objects == NULL) { std::cout << "Realloc failed!" << std::endl; return; }    
    objectCount++;


    // Initialize the object
    objects[objectCount - 1].sprite.Initialize();
    objects[objectCount - 1].Initialize(x, y, serverObject);   

    // Load the texture
    if(!multiple) objects[objectCount - 1].sprite.loadAsSingle  (renderer, path, x, y, w, h);
    else          objects[objectCount - 1].sprite.loadAsMultiple(renderer, path, x, y, w, h);     
}

void Room::Update(){
    // Update objects
    for(int i = 0; i < objectCount; i++) objects[i].Update(false);
}