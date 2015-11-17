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

#ifndef FONT_HPP
#define FONT_HPP

#include <iostream>
#include <array>

#include <SDL2/SDL.h>

#include "font_manager.hpp"

/**
 * @brief
 */
class Font : protected FontManager
{
private:
    // The rect which will contain information about where the font will be
    // rendered.
    SDL_Rect font_rect;
    // Surface used to carry the result of TTF_RenderText(...)
    SDL_Surface* m_pFSurface;
    // The texture that will be printed on the screen.
    SDL_Texture* m_pFTexture;
    // The name of the font used.
    std::string font_name;

public:
    /**
     * @brief The font_type enum that describes the three kind of fonts used in
     * the game.
     */
    enum class FontType
    {
        font_normal,
        font_bold,
        font_extra_bold
    };

public:
    Font(SDL_Rect& font_rect_);
    ~Font();

    /**
     * @brief open_font, function to initialize a font to be used with
     * render_text_solid(...).
     * @param font_type the type of the font, @see FontType.
     * @param size the size of the font.
     */
    void open_font(FontType font_type, int size);

    /**
     * @brief render_text_solid, function to render a solid text onto the game
     * window.
     * @param text the text which will be rendered on the game window.
     */
    void render_text_solid(const std::string& text);

    /**
     * @brief render_text_shaded
     * @param text
     */
    void render_text_shaded(const std::string& text);

    /**
     * @brief font_color is a function to set the color of the font.
     * @param r - red
     * @param g - green
     * @param b - blue
     * @param a - alpha
     */
    void font_color(std::uint8_t r, std::uint8_t g, std::uint8_t b,
                    std::uint8_t a);

    /**
     * @brief font_color is a function to set the color of the font.
     * @param colors is an array that contain information about the 3 colors,
     * plus an alpha.
     */
    void font_color(std::array<std::uint8_t, 4> colors);
};

#endif // FONT_HPP
