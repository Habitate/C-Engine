#ifndef ROOM_H
#define ROOM_H

#include <SDL2/SDL.h>
#include "Object.h"
#include "Texture.h"

class Room
{
    public:
        Room();
        ~Room();

        void Initialize(SDL_Window* window, SDL_Renderer* renderer);

        void CreateObject(int x, int y, int w, int h, const char* path, bool multiple, bool serverObject);

        void Update();

        void Render();

        SDL_Window*   window  ;
        SDL_Renderer* renderer;

        Object * objects ; int objectCount ;
        Texture* texts   ; int textCount   ;
        Texture* textures; int textureCount;
};

#endif // ROOM_H