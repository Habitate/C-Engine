#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>

class Sound{
    public:
        Sound() noexcept;
        Sound(const std::string& path) noexcept;
        
        // Copyable
        explicit Sound(const Sound& object);
        Sound& operator=(const Sound& object);

        // Moveable
        explicit Sound(Sound&& object) noexcept;
        Sound& operator=(Sound&& object) noexcept;

        ~Sound() noexcept;

        //*----------------------------------------------------

        void play();
        void load(const std::string& path);

    private:
        std::shared_ptr<Mix_Music> music;
        std::string path;

        static const int audio_rate;
        static const int audio_channels;
        static const int audio_buffers;

        static const Uint16 audio_format;
};