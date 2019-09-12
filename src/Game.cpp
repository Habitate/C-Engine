#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <exception>

#include <iostream>
#include "functions.h"
#include "color.h"
#include <memory>

#include "obj/player.h"
#include "input.h"
#include "font.h"

#include <string>

Game::Game(const std::string& name, const int x, const int y, const int w, const int h, const unsigned int flags) :
running(false), WREZ(w), HREZ(h), event{0}, renderer(nullptr, SDL_DestroyRenderer), window(nullptr, SDL_DestroyWindow),
White{255, 255, 255, 255}, wallpaper(), ground(), objects(), fnt_ubuntu("../font/Ubuntu.ttf"), tempText(),
tempTextSrcRect{0, 0, 0, 0}, tempTextDstRect{0, 0, 0, 0}, camera(SDL_Rect{0, 0, w, h}){
    window = std::unique_ptr<SDL_Window  , void(*)(SDL_Window  *)>(SDL_CreateWindow(name.c_str(), x, y, w, h, flags), SDL_DestroyWindow);  
    if(!window){
        throw std::runtime_error(std::string("Unable to create window!\n\t") + SDL_GetError());
    }

    renderer = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>(SDL_CreateRenderer(window.get(), -1, 0) , SDL_DestroyRenderer);
    if(!renderer){
        throw std::runtime_error(std::string("Unable to create renderer!\n\t") + SDL_GetError());
    }

    changeIcon("../assets/icont.png");
}
Game::~Game(){
    SDL_Quit();
}

void Game::Initialize(){
    InputHandler::Init();

    objects.reserve(10);

    objects.emplace_back(new Obj_player(this, renderer.get(), &camera, &event));
    //objects.emplace_back(new Obj_player2(renderer.get(), &event, objects[0]->sprite));

    wallpaper.load_single(renderer.get(), "../assets/wallpaper2.jpg");
    wallpaper.set_dimensions(WREZ, HREZ);

    ground.load_single(renderer.get(), "../assets/tilee.jpg");
    ground.set_dimensions(64, 64);

    tempText = fnt_ubuntu.render_text(renderer.get(), "Hello there, text here!", White);
    SDL_QueryTexture(tempText.get(), nullptr, nullptr, &tempTextSrcRect.w, &tempTextSrcRect.h);
    tempTextDstRect = tempTextSrcRect;

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
    for(const std::unique_ptr<Object>& object : objects){
        object->begin_step();
    }
    for(const std::unique_ptr<Object>& object : objects){
        object->step();
    }
    for(const std::unique_ptr<Object>& object : objects){
        object->end_step();
    }
}
void Game::Render(){
    // Clear the screen
    SDL_RenderClear(renderer.get());

    wallpaper.draw(camera, 0, 0);

    // Draw the ground

    const int ground_y = HREZ - ground[0].get_dst_rect().h;
    for(int x = 0; x < WREZ; x += 64){
        ground.draw(camera, x, ground_y);
    }

    // Draw the objects
    for(const std::unique_ptr<Object>& object : objects){
        object->draw();
    }

    //for(int i = 0; i < 100000; ++i);
    //fnt_ubuntu.draw_text(renderer.get(), "Hello there, text here", 0, 0, White);
    SDL_RenderCopy(renderer.get(), tempText.get(), &tempTextSrcRect, &tempTextDstRect);
    
    // Place everything on the screen
    SDL_RenderPresent(renderer.get());
}

void Game::changeIcon(const std::string& path){
    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> icon(IMG_Load(path.c_str()), SDL_FreeSurface);

    //Error check
    if(!icon){
        std::cout << C(C::RED) << "Failed loading icon: " << C(C::DEFAULT) << path << "\n";
        return;
    }

    SDL_SetWindowIcon(window.get(), icon.get());
}
bool Game::isRunning(){
    return running;
}