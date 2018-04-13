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

#include "font_manager.hpp"
#include "debug.hpp"

FontManager::FontManager()
{
    m_pFont = nullptr;
    m_ttf_opened = false;

    // Default font color is white and alpha channel set to 1.
    m_color.r = 0xff;
    m_color.b = 0xff;
    m_color.g = 0xff;
    m_color.a = 1;

    // Default font shade color is white and alpha channel set to 1.
    m_color_shaded.r = 0x00;
    m_color_shaded.b = 0x00;
    m_color_shaded.g = 0x00;
    m_color_shaded.a = 1;

    m_ttf_opened = initialize_sdl_ttf();
}

FontManager::~FontManager()
{
    TTF_CloseFont(m_pFont);
    TTF_Quit();
}

bool FontManager::initialize_sdl_ttf()
{
    if(m_ttf_opened)
    {
        return true;
    }
    else
    {
        if(TTF_Init() != 0)
        {
            Debug::log_err("Some problem ocurred trying to initialize Font \
                          system", TTF_GetError());
            return false;
        }
        else
        {
            Debug::log("Font system initialized.");
            return true;
        }
    }
}
