#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

class Camera{
    public:
        explicit Camera() noexcept;
        explicit Camera(const SDL_Rect& rect) noexcept;
        explicit Camera(const int x, const int y, const float amp) noexcept;

        // Copyable
        explicit Camera(const Camera& camera) noexcept;
        Camera& operator=(const Camera& camera) noexcept;

        // Moveable
        explicit Camera(Camera&& camera) noexcept;
        Camera& operator=(Camera&& camera) noexcept;

        ~Camera() noexcept;

        void move_horizontal(const int dist = 1) noexcept;
        void move_vertical(const int dist = 1) noexcept;

        void zoom_in(const double amount = 1) noexcept;
        void zoom_out(const double amount = 1) noexcept;

        int get_x() const noexcept;
        int get_y() const noexcept;
        double get_amp() const noexcept;

    private:
        int x, y;
        double amp;
};

#endif // CAMERA_H