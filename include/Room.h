#ifndef ROOM_H
#define ROOM_H

//#include <SDL2/SDL.h>

#include <vector>
#include <memory>
#include "Object.h"
#include "Sprite.h"

class Room{
    public:
        void add_object(Object* object);
        void add_sprite(Sprite* sprite);
        void add_texture(Texture* texture);

        void draw(){
            
        }

    private:
        std::vector<std::unique_ptr<Object>> objects;
        std::vector<std::unique_ptr<Sprite>> sprites;
        std::vector<std::unique_ptr<Texture>> textures;
};

#endif // ROOM_H