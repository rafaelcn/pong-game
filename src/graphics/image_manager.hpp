#pragma once

#include <cstdint>
#include <array>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/**
 * @brief The ImageSubsystem class provide functions to load BMP and PNG images.
 */
class ImageManager
{
private:
    static bool m_image_opened;
public:
    ImageManager();
    ~ImageManager();

    /**
     * @brief Function to load BMP images and then return a pointer to the
     * surface that contains the image.
     * @param The path to where the image is located.
     * @param The color to be interpreted as transparent.
     * @return A pointer to a surface which contains the image.
     */
    SDL_Surface* load_bmp(const std::string& path, int color_key_state, const std::array<std::uint32_t, 3>& color_key);

    /**
     * @brief Function to load BMP images and then return a pointer to the
     * surface that contains the image.
     * @param The path to where the image is located.
     * @param The color to be interpreted as transparent.
     * @return A pointer to a surface which contains the image.
     */
    SDL_Surface* load_bmp(const std::string &path, const std::array<std::uint32_t, 3>& color_key);

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
