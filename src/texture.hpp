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

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "image.hpp"

/**
 * @brief This class is a wrapper the SDL_Texture and also offers a set of
 * functions.
 */
class Texture {
private:
    // A raw pointer to a SDL_Texture struct, it represents the actual texture.
    SDL_Texture* m_pTTexture;
    // Position and size of the texture on the renderer.
    SDL_Rect image_rect;
public:
    Texture();
    ~Texture();

    /**
     * @brief load_texture Create a texture from a SDL_Surface struct.
     * @param image_surface The surface containing the image.
     * @param width The width of the texture.
     * @param height The height of the texture.
     * @param coordinate_x The location of the texture on the x axis.
     * @param coordinate_y The location of the texture on the y axis.
     */
    void load_texture(SDL_Surface* image_surface, const int width,
                      const int height, const int coordinate_x,
                      const int coordinate_y);

    /**
     * @brief This function just "blit"(SDL 1.2) the texture on the
     * renderer.
     */
    void show();
};

#endif // TEXTURE_HPP
