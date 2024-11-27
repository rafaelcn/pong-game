#include <memory>

#include <SDL2/SDL_ttf.h>

#include "font.hpp"
#include "debug.hpp"

#include "graphics/window.hpp"

Font::Font(std::shared_ptr<Window> window, SDL_Rect &rect) : FontManager()
{
  m_window = window;
  m_rect = rect;
}

Font::~Font() {
  TTF_CloseFont(m_font);
}

void Font::open_font(FontType type, int size)
{
  if (!m_ttf_opened) {
    Debug::log_err("the font subsystem was not initialized");
    return;
  }

  switch (type) {
  case FontType::normal:
    m_name = "res/fonts/OpenSans-Regular.ttf";
    break;
  case FontType::bold:
    m_name = "res/fonts/OpenSans-Bold.ttf";
    break;
  case FontType::extra_bold:
    m_name = "res/fonts/OpenSans-ExtraBold.ttf";
    break;
  default:
    break;
  }

  m_font = TTF_OpenFont(m_name.c_str(), size);

  if (m_font == nullptr) {
    Debug::log_err("failed to load the font ", m_name, ", reason: ", TTF_GetError());
  }
}

void Font::render_text_solid(const std::string &text)
{
  render_text(FontStyle::solid, text);
}

void Font::render_text_shaded(const std::string& text)
{
  render_text(FontStyle::shaded, text);
}

void Font::render_text(const FontStyle style, const std::string& text)
{
  
  if (m_font == nullptr) {
    Debug::log_err("the font subsystem was not initialized");
    return;
  }

  SDL_Surface* surface = nullptr;
  
  switch (style) {
  case FontStyle::shaded:
	surface = TTF_RenderText_Shaded(m_font, text.c_str(), m_color, m_color_shaded);
	break;
  case FontStyle::solid:
    surface = TTF_RenderText_Solid(m_font, text.c_str(), m_color);
  	break;
  }

  if (surface == nullptr) {
    Debug::log_err("failed to render the font ", m_name);
    return;
  }

  auto texture = SDL_CreateTextureFromSurface(m_window->get_renderer(), surface);

  SDL_FreeSurface(surface);

  if (texture == nullptr) {
    Debug::log_err("failed to create texture from the surface, reason: ", TTF_GetError());
    return;
  }

  SDL_RenderCopy(m_window->get_renderer(), texture, nullptr, &m_rect);
  SDL_DestroyTexture(texture);
}

void Font::font_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
  m_color.r = r;
  m_color.b = g;
  m_color.g = b;
  m_color.a = a;
}

void Font::font_color(std::array<std::uint8_t, 4> colors)
{
  m_color.r = colors[0];
  m_color.b = colors[1];
  m_color.g = colors[2];
  m_color.a = colors[3];
}
