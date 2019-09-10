#include "camera.h"

Camera::Camera() noexcept : x(0), y(0), amp(1){}
Camera::Camera(const SDL_Rect& rect) noexcept : x(rect.x), y(rect.y), amp(1){}
Camera::Camera(const int x, const int y, const float amp) noexcept: x(x), y(y), amp(amp){}

// Copyable
Camera::Camera(const Camera& camera) noexcept = default;
Camera& Camera::operator=(const Camera& camera) noexcept = default;

// Moveable
Camera::Camera(Camera&& camera) noexcept = default;
Camera& Camera::operator=(Camera&& camera) noexcept = default;

Camera::~Camera() noexcept = default;

void Camera::move_horizontal(const int dist) noexcept{
    x -= dist;
}
void Camera::move_vertical(const int dist) noexcept{
    y -= dist;
}

void Camera::zoom_in(const double amount) noexcept{
    amp += amount;
}
void Camera::zoom_out(const double amount) noexcept{
    amp -= amount;
}

int Camera::get_x() const noexcept{
    return x;
}
int Camera::get_y() const noexcept{
    return y;
}
double Camera::get_amp() const noexcept{
    return amp;
}//