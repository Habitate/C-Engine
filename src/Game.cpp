#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <exception>

#include <iostream>
#include "Functions.h"
#include "color.h"
#include <memory>

#include "Objects/player.h"
#include "InputHandler.h"

Game::Game(const char* name, int x, int y, int w, int h, int flags) :
running(false), WREZ(w), HREZ(h), input(0), renderer(nullptr, SDL_DestroyRenderer), window(nullptr, SDL_DestroyWindow), Sans(nullptr, TTF_CloseFont){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    TTF_Init();

    window = std::unique_ptr<SDL_Window  , void(*)(SDL_Window  *)>(SDL_CreateWindow(name, x, y, w, h, flags), SDL_DestroyWindow);  
    if(!window){
        std::cout << SDL_GetError() << "\n\n";
        throw;
    }

    renderer = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>(SDL_CreateRenderer(window.get(), -1, 0) , SDL_DestroyRenderer);
    if(!renderer){
        std::cout << SDL_GetError() << "\n\n";
        throw;
    }

    changeIcon("../assets/icont.png");
}
Game::~Game(){
    SDL_Quit();
}

void Game::Initialize(){
    InputHandler::Init();

    objects.reserve(10);

    objects.emplace_back(new Obj_player(renderer.get(), &event));

    wallpaper.load(renderer.get(), "../assets/wallpaper");

    ground.load(renderer.get(), "../assets/tilee");
    ground.setSize(0, 64, 64);

    running = true;
}
void Game::HandleSDLEvents(){
    //? InputHandler::syncStates() needs to be called before SDL_PollEvent, since SDL_PolLEvent implicitly calls SDL_PumpEvents which updates the keyboard state
    InputHandler::syncStates();
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT: running = false; break;
    }
}
void Game::Update(){

    // Handle object steps
    for(std::unique_ptr<Object>& object : objects){
        object->begin_step();
    }
    for(std::unique_ptr<Object>& object : objects){
        object->step();
    }
    for(std::unique_ptr<Object>& object : objects){
        object->end_step();
    }
}
void Game::Render(){
    // Clear the screen
    SDL_RenderClear(renderer.get());

    wallpaper.draw(renderer.get(), 0, 0);

    // Draw the ground
    for(int x = 0; x < 640; x += 64){
        ground.draw(renderer.get(), x, 416);
    }

    for(std::unique_ptr<Object>& object : objects){
        object->draw(renderer.get());
    }

    // Place everything on the screen
    SDL_RenderPresent(renderer.get());
}

void Game::changeIcon(const std::string& path){
    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> icon(IMG_Load(path.c_str()), SDL_FreeSurface);

    //Error check
    if(!icon){
        std::cout << Color(12) << "Failed loading icon: " << Color(7) << path << "\n";
        return;
    }

    SDL_SetWindowIcon(window.get(), icon.get());
}
bool Game::isRunning(){
    return running;
}