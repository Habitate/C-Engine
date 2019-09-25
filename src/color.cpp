#include "color.h"

#include "windows.h"
#include <ostream>

C::C() noexcept: color(DEFAULT){}
C::C(const uint8_t color) noexcept: color(color){}

// Copyable
C::C(const C& color) noexcept = default;
C& C::operator=(const C& color) noexcept = default;

// Moveable
C::C(C&& color) noexcept = default;
C& C::operator=(C&& color) noexcept = default;

C::~C() noexcept = default;

//*----------------------------------------------------

std::ostream& operator<<(std::ostream& stream, const C& color){
    SetConsoleTextAttribute(C::output_handle, color.color);
    
    return stream;
}

const HANDLE C::output_handle(GetStdHandle(STD_OUTPUT_HANDLE));