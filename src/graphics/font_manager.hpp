#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * @brief The FontManager class is a wrapper to the sdl-ttf API.
 */
class FontManager
{
protected:
  // Internal struct containing font information.
  TTF_Font* m_font;
  // Internal struct containing R, G, B, A information, will be used as the
  //font color.
  SDL_Color m_color;
  // Internal strucut containing shade color information, it will only be used
  //if render_text_shaded().
  SDL_Color m_color_shaded;
  
  // A boolean storing the SDL_TTF initialization state.
  static bool m_ttf_opened;
public:
  FontManager();
  ~FontManager();
};
