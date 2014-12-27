#ifndef FONT_HPP
#define FONT_HPP

#include <stdint.h>
#include <iostream>

#include <SDL2/SDL.h>

#include "font_manager.hpp"

class Font : protected FontManager
{
private:
    // The rect which will contain information about where the font will be
    // rendered.
    SDL_Rect* m_pFRect;
    // Surface used to carry the result of TTF_RenderText...
    SDL_Surface* m_pFSurface;
    // The texture that will be printed on the screen.
    SDL_Texture* m_pFTexture;
    // The renderer used by the font.
    SDL_Renderer* m_pFRenderer;
public:
    Font(SDL_Renderer *font_renderer, SDL_Rect *font_rect);
    ~Font();

    /**
     * @brief The font_type enum
     */
    enum class FontType
    {
        font_normal,
        font_bold,
        font_extra_bold
    };

    /**
     * @brief open_font
     * @param font_type
     * @param size
     */
    void open_font(FontType font_type, int size);

    void render_text_solid(std::string text);
    void render_text_solid(const char* text);

    void render_text_shaded(std::string text);
    void render_text_shaded(const char* text);

    /**
     * @brief font_color
     * @param r
     * @param g
     * @param b
     * @param a
     */
    void font_color(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);
    /**
     * @brief font_color
     * @param colors
     */
    void font_color(u_int8_t colors[3]);



};

#endif // FONT_HPP
