#include "color.h"
#include "windows.h"
#include <ostream>

int C::RED = 12;
int C::CYAN = 11;
int C::GREEN = 10;
int C::YELLOW = 14;
int C::DEFAULT = 7;

C::C(int color) : color(color){}
C::C() : color(DEFAULT){}

C::~C() = default;

std::ostream& operator<<(std::ostream& ss, C color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color.color);
    return ss;
}