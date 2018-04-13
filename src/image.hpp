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

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include <array>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/**
 * @brief The Image class provide functions to load BMP and PNG images.
 */
class Image
{
private:
    //
    bool m_image_opened;
public:
    Image();
    ~Image();

    /**
     * @brief is_open
     * @return A boolean represeting the image system state.
     */
    bool is_open();

    /**
     * @brief Function to load BMP images and then return a pointer to the
     * surface that contains the image.
     * @param The path to where the image is located.
     * @param The color to be interpreted as transparent.
     * @return A pointer to a surface which contains the image.
     */
    SDL_Surface* load_bmp(const std::string& path, int color_key_state,
                                 std::array<std::uint32_t, 3> color_key);

    /**
     * @brief Function to load BMP images and then return a pointer to the
     * surface that contains the image.
     * @param The path to where the image is located.
     * @param The color to be interpreted as transparent.
     * @return A pointer to a surface which contains the image.
     */
    SDL_Surface* load_bmp(const std::string &path,
                                std::array<std::uint32_t, 3>& color_key);

    /**
      * @brief Function to load BMP images and then return a pointer to the
      * surface that contains the image.
      * @param The path to where the image is located.
      * @return A pointer to a surface which contains the image.
      */
    SDL_Surface* load_bmp(const std::string& path);

    /**
     * @brief Function to load PNG images and then return a pointer to the
     * surface that contains the image.
     * @param The path to where the image is located.
     * @return A pointer to a surface which contains the image.
     */
    SDL_Surface* load_png(const std::string& path);
};

#endif // IMAGE_HPP
