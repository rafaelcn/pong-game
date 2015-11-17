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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <array>

#include <SDL2/SDL.h>

/**
 * @brief
 */
class Utils {
public:
    /**
      * @brief Function to load BMP images and then return a pointer to the
      * surface that contains the image.
      * @param The path to where the image is located.
      * @param The color to be interpreted as transparent.
      * @return A pointer to a surface which contains the image.
      */
    static SDL_Surface* load_bmp(const std::string& path, int color_key_state,
                                 std::array<std::uint32_t, 3> color_key);

    /**
     * @brief Function to load BMP images and then return a pointer to the
     * surface that contains the image.
     * @param The path to where the image is located.
     * @param The color to be interpreted as transparent.
     * @return A pointer to a surface which contains the image.
     */
    static SDL_Surface* load_bmp(const std::string &path,
                                std::array<std::uint32_t, 3>& color_key);

    /**
      * @brief Function to load BMP images and then return a pointer to the
      * surface that contains the image.
      * @param The path to where the image is located.
      * @return a pointer to a surface which contains the image.
      */
    static SDL_Surface* load_bmp(const std::string& path);
};

#endif // UTILS_HPP
