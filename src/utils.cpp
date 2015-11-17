#include "utils.hpp"
#include "debug.hpp"
#include "game.hpp"

SDL_Surface* Utils::load_bmp(const std::string& path, int color_key_state,
                             std::array<std::uint32_t, 3> color_key)
{
    SDL_Surface* image_surface = SDL_LoadBMP(path.c_str());

    if(Game::debug_mode) 
    {
        Debug::log("Loading image on path: ", path);
    }

    if(image_surface == nullptr)
    {
        Debug::log_err("Failed to load the image! Due to: ", SDL_GetError());
    }
    else
    {
        Debug::log("Setting color key. State:", color_key_state, " Color-key: ",
                   color_key[0], color_key[1], color_key[2]);
        SDL_SetColorKey(image_surface, color_key_state, 
                        SDL_MapRGB(image_surface->format,
                                   color_key[0],
                                   color_key[1],
                                   color_key[2]));
    }
    return image_surface;
}

SDL_Surface* Utils::load_bmp(const std::string &path, 
                             std::array<std::uint32_t, 3>& color_key)
{
    return load_bmp(path, SDL_TRUE, color_key);
}

SDL_Surface* Utils::load_bmp(const std::string &path)
{
    std::array<std::uint32_t, 3> color_key_{{ 0, 0, 0 }};
    
    return load_bmp(path, SDL_FALSE, color_key_);
}
