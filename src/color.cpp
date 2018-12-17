#include "color.h"
#include "windows.h"
#include <ostream>

std::ostream& operator<<(std::ostream& ss, Color color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color.color);
    return ss;
}