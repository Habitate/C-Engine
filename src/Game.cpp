#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include "Functions.h"
#include "color.h"

Game::Game(){
    running = false;
    connectedToServer = false;
}
Game::~Game(){
    running = false;
}

// Text --->
void Game::InitializeTexts(){
    // Put all text objects here



}
void Game::DoThingsBasedOnInputTexts(char input){
    // Put all behaviour of text here
            
    switch(input){
        case 'a':;
        case 'd':;
        case 's':;
        case 'w':;
    }
    
}
void Game::UpdateTexts(){
    // Update all texts here
            



}
void Game::RenderTexts(){
    // Put all text objects here



}

// Objects --->
void Game::InitializeObjects(){
    // Put all object initialization here

    object1.Initialize(100, 100, false);
    object1.sprite.Load(renderer, "../assets/anim/test2/frame_0.png");
    object1.sprite.ChangeSize(-1, 100, 100);

    object2.Initialize(300, 300, false);
    object2.sprite.Load(renderer, "../assets/anim/test2/frame_25.png");
    object2.sprite.ChangeSize(-1, 100, 100);
            
}
void Game::DoThingsBasedOnInputObjects(char input){
    // Put all behaviour of objects here
            
    switch(input){
        case 'a': object1.x--; break;
        case 'd': object1.x++; break;
        case 's': object1.y++; break;
        case 'w': object1.y--; break;         
    }
            
}
void Game::UpdateObjects(){
    // Update all objects here

    object1.Update(false);
    object2.Update(false);

    //object1.checkMoreCollision(object2);    
}
void Game::RenderObjects(){
    // Put all objects here

    object1.sprite.Draw(renderer, object1.x, object1.y);
    object2.sprite.Draw(renderer, object2.x, object2.y);
}
        
// -------------- //


void Game::Initialize(const char* name, int x, int y, int w, int h, int flags){

    // Error check and init
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    TTF_Init();

    window   = SDL_CreateWindow  (name, x, y, w, h, flags);
    renderer = SDL_CreateRenderer(window, -1, 0);
    changeIcon("../assets/icont.png");

    // Error check
    if(window == NULL || renderer == NULL){
            std::cout << SDL_GetError();
                
            return;
    }

    InitializeObjects();
    InitializeTexts();

    //If everything went fine, continue
    running = true;

    std::cout << "Initialized everything!" << std::endl << std::endl;
}

void Game::HandleSDLEvents(){
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT: Quit(); break;
    }
}

void Game::Update(){
    // Do input stuff
    input = getInput();
    switch(input){    
        // Connect to server
        case 'p':
            if(!connectedToServer){
                DataSocket = StartWinsockClient("192.168.8.106", "27015");
                connectedToServer = true;
            } break;
    }

    DoThingsBasedOnInputObjects(input);
    DoThingsBasedOnInputTexts(input);
    UpdateObjects();
    UpdateTexts();
}

void Game::Render(){
    // Clear the screen
    SDL_RenderClear(renderer);

    RenderObjects();
    RenderTexts();

    // Draw the screen
    SDL_RenderPresent(renderer);
}

void Game::Quit(){
    shutdown(DataSocket, SD_BOTH);
    WSACleanup();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    exit(0);
}

void Game::changeIcon(const char* path){
    // Load the surface
    SDL_Surface* icon = IMG_Load(path);

    //Error check
    if(icon == NULL){
        std::cout << Color(12) << "Failed loading icon: " << Color(7) << path << std::endl;
        SDL_FreeSurface(icon);
        return;
    }

    SDL_SetWindowIcon(window, icon);

    // Free surface
    SDL_FreeSurface(icon);
}

bool Game::isRunning(){
    return running;
}