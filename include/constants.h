#pragma once

#include <array>

namespace Texture_Constants{
    //? Data types supported by the SDL_Image library
    const std::array<std::string, 17> SUPPORTED_DATA_TYPES = {
    	".png", ".jpg", ".jpeg",
        ".bmp", ".gif", ".tga",
        ".pnm", ".pbm", ".pgm",
        ".ppm", ".xpm", ".xcf",
        ".pcx", ".tif", ".tiff",
        ".lbm", ".iff"
    };
}
