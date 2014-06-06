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

SDL_Surface* loadBMP(std::string path)
{
    SDL_Surface* imageSurface = SDL_LoadBMP(path.c_str());

    if(imageSurface == NULL)
    {
        std::cout << "\nLOG_ERR: Failed to load the image! "
             << "\nLOG_ERR: Due to: " << SDL_GetError() << std::endl;
    }

    return imageSurface;
}

void renderTexture(SDL_Surface* imageSurface, SDL_Renderer** renderer,
                   int width, int height, int xCord, int yCord)
{
    SDL_Rect* imageRect = new SDL_Rect();

    imageRect->h = height;
    imageRect->w = width;
    imageRect->x = xCord;
    imageRect->y = yCord;

    SDL_Texture* imageTexture = NULL;

    imageTexture = SDL_CreateTextureFromSurface(*renderer, imageSurface);

    if(imageTexture == NULL)
        std::cout << "LOG_ERR: imageTexture is null, error: " << SDL_GetError()
                  << std::endl;

    SDL_RenderCopy(*renderer, imageTexture, NULL, imageRect);
    //probably a memory leak when calling the function by copying the
    //parameters: width, height, xCord, and yCord.

    //trying to solve that...
    SDL_DestroyTexture(imageTexture);
    delete imageRect;
}
