#include "utils.hpp"
#include "debug.hpp"

SDL_Surface* Utils::load_bmp(const std::string& path,
                             std::array<std::uint32_t, 3> color_key)
{
    SDL_Surface* imageSurface = SDL_LoadBMP(path.c_str());

    if(imageSurface == nullptr)
    {
        Debug::logerr("Failed to load the image! Due to: ", SDL_GetError());
    }
    else
    {
        SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format,
                                                           color_key[0],
                                                           color_key[1],
                                                           color_key[2]));
    }
    return imageSurface;
}

SDL_Surface* Utils::load_bmp(const std::string &path)
{
    SDL_Surface* image_surface = SDL_LoadBMP(path.c_str());

    if(image_surface == nullptr)
    {
        Debug::logerr("Failed to load the image! Due to: ", SDL_GetError());
    }

    return image_surface;
}
