#include "Functions.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <windows.h>
#include <thread>
#include <sys/stat.h> //* Used for file checking

#include "color.h"
#include "string"

void sendPosition(int* x, int* y, SOCKET DataSocket){
    static char positions[5] = {0};

    *((short*)(positions + 0)) = *x;
    *((short*)(positions + 2)) = *y;

    send(DataSocket, positions, 5, 0);
}

void recievePosition(int* x, int* y, SOCKET DataSocket){
    static char positions[5] = {0};
    recv(DataSocket, positions, 5, 0);

    *x = *((short*)(positions + 0));
    *y = *((short*)(positions + 2));
}

// --- Misc --- ///
char* stringWInt(char* buffer, const char* text,int num){
    sprintf(buffer, "%s%d", text, num);
    return buffer;
}

char getInput(){
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_Q]) return 'q';
    if(state[SDL_SCANCODE_W]) return 'w';
    if(state[SDL_SCANCODE_E]) return 'e';
    if(state[SDL_SCANCODE_R]) return 'r';
    if(state[SDL_SCANCODE_T]) return 't';
    if(state[SDL_SCANCODE_Y]) return 'y';
    if(state[SDL_SCANCODE_U]) return 'u';
    if(state[SDL_SCANCODE_I]) return 'i';
    if(state[SDL_SCANCODE_O]) return 'o';
    if(state[SDL_SCANCODE_P]) return 'p';
    if(state[SDL_SCANCODE_A]) return 'a';
    if(state[SDL_SCANCODE_S]) return 's';
    if(state[SDL_SCANCODE_D]) return 'd';
    if(state[SDL_SCANCODE_F]) return 'f';
    if(state[SDL_SCANCODE_G]) return 'g';
    if(state[SDL_SCANCODE_H]) return 'h';
    if(state[SDL_SCANCODE_J]) return 'j';
    if(state[SDL_SCANCODE_K]) return 'k';
    if(state[SDL_SCANCODE_L]) return 'l';
    if(state[SDL_SCANCODE_Z]) return 'z';
    if(state[SDL_SCANCODE_X]) return 'x';
    if(state[SDL_SCANCODE_C]) return 'c';
    if(state[SDL_SCANCODE_V]) return 'v';
    if(state[SDL_SCANCODE_B]) return 'b';
    if(state[SDL_SCANCODE_N]) return 'n';
    if(state[SDL_SCANCODE_M]) return 'm';

    else return 0;
}

// Loader functions

// TTF_RenderText_Blended
bool LoadSDLTexture(SDL_Renderer* renderer, SDL_Surface** loader, SDL_Texture** sprite, SDL_Surface* loaderFunction(TTF_Font*, const char*, SDL_Color), TTF_Font* font, const char* text, SDL_Color text_color){
    // Load the surface and texture
    *loader = loaderFunction(font, text, text_color);
    *sprite = SDL_CreateTextureFromSurface(renderer, *loader);
 
    // Check for loading errors
    if(*loader == NULL || *sprite == NULL)
    std::cout << Color(12) << "Failed loading text: \"" << Color(14) << text << Color(12) << "\"\n" << Color(7);

    // Check for loader surface specific errors
    if(!*loader){
        std::cout << "\n\tLoader == NULL\n\t->" << TTF_GetError() << std::endl;

        std::exit(1);
        return false;
    }
        
    // Check for texture sprite specific errors
    if(!*sprite){
        std::cout << "\n\tSprite == NULL\n\t" << TTF_GetError() << std::endl;

        std::exit(1);
        return false;
    }
    
    // Print "Success" if everything is fine
    std::cout << Color(10) << "Successfully loaded text: \"" << Color(11) << text << Color(10) << "\"\n" << Color(7);

    return true;
}

// IMG_Load
bool LoadSDLTexture(SDL_Renderer* renderer, SDL_Surface** loader, SDL_Texture** sprite, SDL_Surface* loaderFunction(const char*), const char* path){
    // Load the surface and texture
    *loader = loaderFunction(path);
    *sprite = SDL_CreateTextureFromSurface(renderer, *loader);

    // Check for loading errors
    if(*loader == NULL || *sprite == NULL)
    std::cout  << Color(12) << "Failed loading texture: \"" << Color(14) << path << Color(12) << "\"\n" << Color(7);

    // Check for loader surface specific errors
    if(!*loader){
        std::cout << "\n\tLoader == NULL\n\t-> " << SDL_GetError() << std::endl;

        std::exit(1);
        return false;
    }

    // Check for texture sprite specific errors   
    if(!*sprite){
        std::cout << "\n\tSprite == NULL\n\t" << SDL_GetError() << std::endl;

        std::exit(1);
        return false;
    }

    // Print "Success" if everything is fine
    std::cout << Color(10) << "Successfully loaded texture: \"" << Color(14) << path << Color(10) << "\"\n" << Color(7);

    return true;
}

bool fileExists(std::string path){
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

//? Both return false if the file does not contain an extension
bool getExtensionStart(std::string fileName, int& pos){
    for(int i = fileName.size() - 1; i > 0; --i)
    if(fileName[i] == '.'){
        pos = i;
        return fileName[i + 1] != '\0' && fileName[i + 1] != '\\' && fileName[i + 1] != '/';
    }
    
    return false;
}
bool cutExtension(std::string& file, std::string& ext){
    int extPos(0);

    if(getExtensionStart(file, extPos)){
        ext.insert(0, file, extPos, file.size() - extPos);
        file.erase(extPos);

        return true;
    }

    return false;
}