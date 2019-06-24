#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <exception>

#include <iostream>
#include "Functions.h"
#include "color.h"
#include <memory>

Game::Game(const char* name, int x, int y, int w, int h, int flags)
: running(false), WREZ(w), HREZ(h), input(0), renderer(nullptr, SDL_DestroyRenderer), window(nullptr, SDL_DestroyWindow), Sans(nullptr, TTF_CloseFont){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    TTF_Init();

    window   = std::unique_ptr<SDL_Window  , void(*)(SDL_Window  *)>(SDL_CreateWindow(name, x, y, w, h, flags), SDL_DestroyWindow);
    if(!window  ) { std::cout << SDL_GetError() << "\n\n"; throw; }

    renderer = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>(SDL_CreateRenderer(window.get(), -1, 0) , SDL_DestroyRenderer);
    if(!renderer) { std::cout << SDL_GetError() << "\n\n"; throw; }

    changeIcon("../assets/icont.png");
}
Game::~Game(){
    SDL_Quit();
}

void Game::Initialize(){
    player.sprite.load(renderer.get(), "../assets/anim/test/test");
    player.sprite.setSize(-1, 100, 100);
    player.body = player.sprite.getDstRect();
    player.body.x = 320;
    player.body.y = 316;
    player.sprite.setIndex(34);
    player.sprite.animating = false;
    player.sprite.animationStartIndex = 34;

    wallpaper.load(renderer.get(), "../assets/wallpaper");

    ground.load(renderer.get(), "../assets/tilee");
    ground.setSize(0, 64, 64);

    running = true;
}
void Game::HandleSDLEvents(){
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT: running = false; break;
    }
}
void Game::Update(){
    // Do input stuff
    switch(getInput()){
        case 'a': player.body.x -= 3; break;
        case 'd': player.body.x += 3; break;

        case 'w':   if(!player.sprite.animatingOnce){
                        player.sprite.setIndex(34);
                        player.sprite.runAnimationOnce();
                    }
    }

    player.update();
}
void Game::Render(){
    // Clear the screen
    SDL_RenderClear(renderer.get());

    wallpaper.draw(renderer.get(), 0, 0);

    // Draw the ground
    for(int x = 0; x < 640; x += 64){
        ground.draw(renderer.get(), x, 416);
    }

    //player.sprite.draw(renderer.get(), 320, 316);
    player.draw(renderer.get());

    // Draw the screen
    SDL_RenderPresent(renderer.get());
}

void Game::changeIcon(const char* path){
    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> icon(IMG_Load(path), SDL_FreeSurface);

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