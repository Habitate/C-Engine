#include "room.h"
#include <algorithm>

void Room::add_object(Object* object){
    objects.emplace_back(object);

    sort(objects.begin(), objects.end(), [](const Object& obj1, const Object& obj2){
        return obj1.sprite.get_depth() < obj2.sprite.get_depth();
    });
}
void Room::add_sprite(Sprite* sprite){
    sprites.emplace_back(sprite);
    
    sort(sprites.begin(), sprites.end(), [](const Sprite& obj1, const Sprite& obj2){
        return obj1.get_depth() < obj2.get_depth();
    });
}
void Room::add_texture(Texture* texture){
    textures.emplace_back(texture);
    
    sort(textures.begin(), textures.end(), [](const Texture& obj1, const Texture& obj2){
        return obj1.get_depth() < obj2.get_depth();
    });
}