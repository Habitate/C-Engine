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
    
        C() noexcept;
        C(const uint8_t color) noexcept;

        // Copyable
        explicit C(const C& color) noexcept;
        C& operator=(const C& color) noexcept;

        // Moveable
        explicit C(C&& color) noexcept;
        C& operator=(C&& color) noexcept;

        ~C() noexcept;

        //*----------------------------------------------------

        friend std::ostream& operator<<(std::ostream& stream, const C& color);

    private:
        static const HANDLE output_handle;

        uint8_t color;
};