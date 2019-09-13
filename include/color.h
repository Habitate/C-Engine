#pragma once

#include <ostream>
#include "windows.h"

class C{
    public:
        enum Colors : uint8_t{
            DEFAULT = 7,

            RED = 12,
            PINK = 13,
            BLUE = 9,
            CYAN = 11,
            GREEN = 10,
            WHITE = 15,
            YELLOW = 14,
            PURPLE = 5
        };

        static const HANDLE OUTPUT_HANDLE;
    
        C(const uint8_t color) noexcept;
        C() noexcept;

        ~C();

        friend std::ostream& operator<<(std::ostream& ss, const C& color);

    private:
        uint8_t color;
};