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

#include "image.hpp"
#include "debug.hpp"

Image::Image()
{
    if (!m_image_opened) {
        if (IMG_Init(IMG_INIT_PNG) != 0) {
            Debug::log_err("Image system couldn't be initialized. Due to:",
                        IMG_GetError());

            m_image_opened = false;
        }
        else {
            Debug::log("Image system initialized.");
            m_image_opened = true;
        }
    }
    else {
        Debug::log("Image system initialized.");
    }
}

Image::~Image()
{

}

bool Image::is_open()
{
    return m_image_opened;
}

SDL_Surface* Image::load_bmp(const std::string& path, int color_key_state,
                             std::array<std::uint32_t, 3> color_key)
{
    SDL_Surface* image = SDL_LoadBMP(path.c_str());

    if (image == nullptr) {
        Debug::log_err("Failed to load the image! Due to: ", SDL_GetError());
    }
    else {
        SDL_SetColorKey(image, color_key_state, SDL_MapRGB(
                        image->format,
                        color_key[0], color_key[1], color_key[2]));
    }
    return image;
}

SDL_Surface* Image::load_bmp(const std::string &path,
                             std::array<std::uint32_t, 3>& color_key)
{
    return load_bmp(path, SDL_TRUE, color_key);
}

SDL_Surface* Image::load_bmp(const std::string &path)
{
    std::array<std::uint32_t, 3> color_key_{{ 0, 0, 0 }};

    return load_bmp(path, SDL_FALSE, color_key_);
}

SDL_Surface* Image::load_png(const std::string &path)
{
    SDL_Surface* image = nullptr;
    SDL_RWops* rwop = nullptr;

    if (m_image_opened) {
        rwop = SDL_RWFromFile(path.c_str(), "rb");

        image = IMG_LoadPNG_RW(rwop);

        if (image == nullptr) {
            Debug::log_err("Failed to load the image! Due to: ", SDL_GetError());
        }
    }
    return image;
}
