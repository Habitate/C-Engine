#ifndef COLOR_H
#define COLOR_H

#include <ostream>
#include <string>

class C{
    public:
        C(int color);
        C();

        ~C();

        friend std::ostream& operator<<(std::ostream& ss, C color);

        int color;

        //* Color definitions
        static int RED;
        static int CYAN;
        static int GREEN;
        static int YELLOW;
        static int DEFAULT;
};

#endif // COLOR_H