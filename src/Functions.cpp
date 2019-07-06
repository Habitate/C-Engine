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

bool fileExists(const std::string& path){
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

//? Both return false if the file does not contain an extension
bool getExtensionStart(const std::string& fileName, unsigned int& pos){
    for(unsigned int i = fileName.size() - 1; i > 0; --i){
        if(fileName[i] == '.'){
            pos = i;
            return fileName[i + 1] != '\0' && fileName[i + 1] != '\\' && fileName[i + 1] != '/';
        }
    }
    
    return false;
}
bool cutExtension(std::string& file, std::string& ext){
    unsigned int extPos(0);

    if(getExtensionStart(file, extPos)){
        ext.insert(0, file, extPos, file.size() - extPos);
        file.erase(extPos);

        return true;
    }

    return false;
}