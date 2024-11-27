#pragma once

#include <string>
#include <cstdint>
#include <array>
#include <memory>

#include <SDL2/SDL.h>

#include "font_manager.hpp"
#include "window.hpp"

/**
 * @brief The Font class extends the FontManager and is responsible to offer
 * a clean API to open and render fonts onto the screen.
 */
class Font : protected FontManager
{
private:
  // The rect which will contain information about where the font will be
  // rendered.
  SDL_Rect m_rect;
  // The name of the font used.
  std::string m_name;

  std::shared_ptr<Window> m_window;
public:
  /**
   * @brief Describes the three kind of fonts used in the game.
   */
  enum class FontType
    {
      normal,
      bold,
      extra_bold
    };
  
  /**
   * @brief Abstracts the styles on which a font can be rendered
   */
  enum class FontStyle
    {
      solid,
	  shaded
    };
public:
  Font(std::shared_ptr<Window> window, SDL_Rect& rect);
  ~Font();
  
    /**
     * @brief open_font, function to initialize a font to be used with
     * render_text_solid(...).
     * @param font_type the type of the font, @see FontType.
     * @param size the size of the font.
     */
    void open_font(FontType font_type, int size);

    /**
     * @brief render_text_solid renders a solid text onto the game window.
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
    void font_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

    /**
     * @brief font_color is a function to set the color of the font.
     * @param colors is an array that contain information about the 3 colors,
     * plus an alpha.
     */
    void font_color(std::array<std::uint8_t, 4> colors);
private:
    void render_text(const FontStyle style, const std::string& text);
};
