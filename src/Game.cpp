#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <exception>

#include <iostream>
#include "Functions.h"
#include "color.h"

Game::Game(const char* name, int x, int y, int w, int h, int flags) : running(false), WREZ(w), HREZ(h) {
    // Error check and init
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    TTF_Init();

    window = SDL_CreateWindow  (name, x, y, w, h, flags);
    if(!window) { std::cout << SDL_GetError() << "\n\n"; throw; }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) { std::cout << SDL_GetError() << "\n\n"; throw; }

    changeIcon("../assets/icont.png");

    running = true;
    std::cout << "Initialized framework!\n\n";
}

void Game::Initialize(){
    t.Load(renderer, "../assets/icont");

    std::cout << "\nInitialized all objects!\n\n";
}

void Game::HandleSDLEvents(){
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT: Quit(); break;
    }
}

void Game::Update(){
    // Do input stuff
    switch(getInput()){    
    }
}

void Game::Render(){
    // Clear the screen
    SDL_RenderClear(renderer);

    t.Draw(renderer, 0, 0);
    t.ChangeSize(-1, 640, 480);

    // Draw the screen
    SDL_RenderPresent(renderer);
}

void Game::Quit(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    exit(0);
}

void Game::changeIcon(const char* path){
    // Load the surface
    SDL_Surface* icon = IMG_Load(path);

    //Error check
    if(!icon){
        std::cout << Color(12) << "Failed loading icon: " << Color(7) << path << "\n";
        SDL_FreeSurface(icon);

        return;
    }

    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
}

bool Game::isRunning(){
    return running;
}