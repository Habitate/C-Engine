#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

class Texture
{
    public:
        Texture();
        ~Texture();

        void Initialize();

        void startAnimation(bool once);

        void stopAnimation();

        void updateAnimation();

        void errorCheck(SDL_Surface*, SDL_Texture**, char*, int);

        void loadAsMultiple(SDL_Renderer*, const char*, int, int, int, int);

        void loadAsSingle(SDL_Renderer*, const char*, int, int, int, int);

        void draw(SDL_Renderer*);

        // Variables
        bool good, animateable, visable, animateOnce;
        int animator, animations;

        SDL_Texture** sprite;
        SDL_Rect srcRect;
        SDL_Rect dstRect;   
};

#endif // TEXTURE_H