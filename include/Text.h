// *********************************************************
// This class's objects hugely rely on the constructor!
// Make sure it's allways called when dealing with dynamic
// memory! Also, every intance of the object must first be
// Initialized with the functions
// *********************************************************

#ifndef TEXT_H
#define TEXT_H

#define TEXTSIZE 50
#define FONTPATHSIZE 50
#define DEFAULTFONTSIZE 24
#define DEFAULTFONTCOLOR {255, 255, 255}
#define DEFAULTFONT "Fonts/Ubuntu.ttf"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text
{
    public:
        Text();
        Text(const Text&);
        ~Text();
        Text& operator=(const Text&);
        Text& operator=(const char*);

        // Functionality functions
        void Initialize(SDL_Renderer*, const char*, const char* , int, SDL_Color, int, int, bool, int*);
        void Initialize(SDL_Renderer*, const char*, int, int);
        void Draw();
        void Load();
        void Update();

        // Manipulation functions       
        void ChangeText(const char*);  
        void ChangeTextColor(SDL_Color);
        void ChangeFont(const char*);
        void ChangeFontSize(int);
        void ChangeRenderer(SDL_Renderer*);
        void ChangeVisability(bool);
        void ChangeLoaderFunction(SDL_Surface* (*loaderFunction)(TTF_Font*, const char*, SDL_Color));
        void ChangeNumber(int*);
        void SetNumericality(bool);
        void SetX(int);
        void SetY(int);

        // Variables
        SDL_Surface* (*loaderFunction)(TTF_Font*, const char*, SDL_Color);

        char text[TEXTSIZE], fontPath[FONTPATHSIZE];
        bool good, visable, numerical;
        int fontSize, *number, oldNumber;

        SDL_Color textColor;
        TTF_Font* font;
        
        SDL_Rect srcRect, dstRect;
        SDL_Renderer* renderer;
        SDL_Texture* sprite; 
};

#endif // TEXT_H