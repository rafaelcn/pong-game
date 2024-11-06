/**
 * Copyright 2014-2018 Rafael Campos Nunes.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain a
 * copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
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
