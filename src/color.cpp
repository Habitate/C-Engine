#include "color.h"

#include "windows.h"
#include <ostream>

const HANDLE C::OUTPUT_HANDLE(GetStdHandle(STD_OUTPUT_HANDLE));

C::C(const uint8_t color) noexcept: color(color){}
C::C() noexcept: color(DEFAULT){}

C::~C() = default;

std::ostream& operator<<(std::ostream& ss, const C& color){
    SetConsoleTextAttribute(C::OUTPUT_HANDLE, color.color);
    
    return ss;
}