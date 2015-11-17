/*
 * Pong Game.
 * Author: Rafael Campos Nunes.
 * License: Apache v2.
 *
 * Fell free to contact me on
 * Email: rafaelnunes737@hotmail.com
 * Github: https://github.com/rafaelcn
 *
 * Also you can contact me on IRC(freenode.net server) my nickname is: ranu.
 */

#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * @brief The FontManager class is a wrapper to the sdl-ttf API.
 */
class FontManager
{
private:
    /**
     * @brief initialize_sdl_ttf initializes the TTF "module"
     * @return The state of TTF_Init.
     */
    bool initialize_sdl_ttf();
protected:
    // Internal struct containing font information.
    TTF_Font* m_pFont;
    // Internal struct containing R, G, B, A information, will be used as the
    //font color.
    SDL_Color m_color;
    // Internal strucut containing shade color information, it will only be used
    //if render_text_shaded().
    SDL_Color m_color_shaded;
    // A boolean storing the SDL_TTF state.
    bool m_ttf_opened;

public:
    FontManager();
    ~FontManager();


};

#endif // FONTMANAGER_HPP
