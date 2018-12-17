#ifndef COLOR_H
#define COLOR_H

#include <ostream>

class Color{
    public:
        Color(int color) : color(color) {}
        ~Color() {}

        friend std::ostream& operator<<(std::ostream&, Color);

        int color;
};

#endif // COLOR_H