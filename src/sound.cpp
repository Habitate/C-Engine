#include "sound.h"
#include <SDL2/SDL_mixer.h>

Sound::Sound() noexcept : music(nullptr, Mix_FreeMusic), path(){}
Sound::Sound(const std::string& path) noexcept : music(Mix_LoadMUS(path.c_str()), Mix_FreeMusic), path(path){}
        
// Copyable
Sound::Sound(const Sound& object) = default;
Sound& Sound::operator=(const Sound& object) = default;

// Moveable
Sound::Sound(Sound&& object) noexcept = default;
Sound& Sound::operator=(Sound&& object) noexcept = default;

Sound::~Sound() noexcept = default;

void Sound::play(){
    Mix_PlayMusic(music.get(), 0);
}
void Sound::load(const std::string& path){
    music = std::shared_ptr<Mix_Music>(Mix_LoadMUS(path.c_str()), Mix_FreeMusic);
}

//*----------------------------------------------------

const int audio_rate(44100);
const int audio_channels(1);
const int audio_buffers(4096);

const Uint16 audio_format(AUDIO_S16); /* 16-bit stereo */