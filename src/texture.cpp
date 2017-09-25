/**
 * Copyright 2014 Rafael Campos Nunes.
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

#include "texture.hpp"
#include "window.hpp"

Texture::Texture()
{
    m_pTTexture = nullptr;
}

Texture::~Texture()
{
    // To have sure that the things will be freed.
    SDL_DestroyTexture(m_pTTexture);
}

void Texture::load_texture(SDL_Surface* image_surface, const int width,
                           const int height, const int coordinate_x,
                           const int coordinate_y)
{
    image_rect.h = height;
    image_rect.w = width;
    image_rect.x = coordinate_x;
    image_rect.y = coordinate_y;

    m_pTTexture = SDL_CreateTextureFromSurface(Window::get_renderer(),
                                               image_surface);

    SDL_FreeSurface(image_surface);

    if(m_pTTexture == nullptr)
    {
        Debug::log_err("Image texture is null on creation! error: ",
                       SDL_GetError());
    }
}

void Texture::show()
{
    if(m_pTTexture == nullptr)
    {
        Debug::log_err("Image texture is null! error: ", SDL_GetError());
    }
    else
    {
        SDL_RenderCopy(Window::get_renderer(), m_pTTexture, nullptr,
                       &image_rect);
    }
}
