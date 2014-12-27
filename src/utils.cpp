#include "utils.hpp"
#include "debug.hpp"

#include <iostream>
#include <stdint-gcc.h>


SDL_Surface* Utils::load_bmp(std::string path, int32_t colorKey[3])
{
    SDL_Surface* imageSurface = SDL_LoadBMP(path.c_str());

    if(imageSurface == nullptr) {
        Debug::logerr("Failed to load the image! Due to: ", SDL_GetError());
    }
    else {
        SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format,
                                                           colorKey[0],
                                                           colorKey[1],
                                                           colorKey[2]));
    }
    return imageSurface;
}

SDL_Surface* Utils::load_bmp(std::string path)
{
    SDL_Surface* image_surface = SDL_LoadBMP(path.c_str());

    if(image_surface == nullptr) {
        Debug::logerr("Failed to load the image! Due to: ", SDL_GetError());
    }

    return image_surface;
}

void Utils::render_texture(SDL_Surface* imageSurface, SDL_Renderer** renderer,
                   int width, int height, int coordinate_x, int coordinate_y)
{
    SDL_Rect* image_rect = new SDL_Rect();

    image_rect->h = height;
    image_rect->w = width;
    image_rect->x = coordinate_x;
    image_rect->y = coordinate_y;

    SDL_Texture* image_texture = nullptr;

    image_texture = SDL_CreateTextureFromSurface(*renderer, imageSurface);

    if(image_texture == nullptr)
       Debug::logerr("image texture is null! error: ", SDL_GetError());

    SDL_RenderCopy(*renderer, image_texture, nullptr, image_rect);
    //probably a memory leak when calling the function by copying the
    //parameters: width, height, xCord, and yCord.

    //trying to solve that...
    SDL_DestroyTexture(image_texture);
    delete image_rect;
}
