#include "utils.hpp"

#include <iostream>
#include <stdint.h>

SDL_Surface* loadBMP(std::string path, int32_t colorKey[3])
{
    SDL_Surface* imageSurface = SDL_LoadBMP(path.c_str());

    if(imageSurface == NULL)
    {
        std::cout << "\nLOG_ERR: Failed to load the image! "
             << "\nLOG_ERR: Due to: " << SDL_GetError() << std::endl;
    }
    else
    {
        /* On this specific game the background is 0x20 so, the implementation
         * follows the background, in the future I'll be implementing one to
         * ~any~ color key.
         */

        SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format,
                                                           colorKey[0],
                                                           colorKey[1],
                                                           colorKey[2]));
    }

    return imageSurface;
}

