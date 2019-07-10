#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

class Font{
    public:
        Font() noexcept;
        Font(const std::string& path, const unsigned int size = 14);

        bool good() const noexcept;

        void set(const std::string& path, const unsigned int size = 14);

        void setSize(const unsigned int size);
        void setFont(const std::string& path);

        const unsigned int& getSize() const noexcept;
        const std::string& getPath() const noexcept;

        void draw_text(SDL_Renderer* const renderer, const std::string& text, const int x, const int y, const SDL_Color& color) const;
        std::shared_ptr<SDL_Texture> render_text(SDL_Renderer* const renderer, const std::string& text, const SDL_Color& color) const;

    private:
        void update();

        std::string path;
        unsigned int size;

        std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> font;
};

#endif // FONT_H