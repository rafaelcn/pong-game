#include "font.hpp"
#include "debug.hpp"

#include <cassert>

Font::Font(SDL_Renderer *font_renderer, SDL_Rect *font_rect) : FontManager()
{
    assert(font_rect != nullptr);

    m_pFSurface     = nullptr;
    m_pFTexture     = nullptr;
    m_pFRect        = font_rect;
    m_pFRenderer    = font_renderer;

    assert(m_pFRenderer != nullptr);
    assert(m_pFRect != nullptr);
}

Font::~Font() {}


void Font::open_font(FontType font_type, int size)
{
    if(!m_ttf_opened) {

    }
    // name of the font depending on the FontType
    std::string font_name;

    switch(font_type)
    {
    case FontType::font_normal:
        font_name = "res/fonts/OpenSans-Regular.ttf";
        break;
    case FontType::font_bold:
        font_name = "res/fonts/OpenSans-Bold.ttf";
        break;
    case FontType::font_extra_bold:
        font_name = "res/fonts/OpenSans-ExtraBold.ttf";
        break;
    default:
        break;
    }

    m_pFont = TTF_OpenFont(font_name.c_str(), size);

    if(m_pFont == nullptr) {
        Debug::logerr("Failed to load the font: ", font_name, " Due to: ",
                      TTF_GetError());
    }
    else {
        Debug::log("Font ", font_name, " loaded successfully.");
    }

}

void Font::render_text_solid(std::string text)
{
    if(m_pFont == nullptr) {
        Debug::logerr("You haven't loaded a font to display it.");
        return;
    }

    m_pFSurface = TTF_RenderText_Solid(m_pFont, text.c_str(), m_color);

    if(m_pFSurface == nullptr) {
        Debug::logerr("");
        return;
    }

    m_pFTexture = SDL_CreateTextureFromSurface(m_pFRenderer, m_pFSurface);

    if(m_pFSurface == nullptr) {
        Debug::logerr("");
        return;
    }

    SDL_RenderCopy(m_pFRenderer, m_pFTexture, nullptr, m_pFRect);

    // Free memory allocated by the texture.
    SDL_DestroyTexture(m_pFTexture);
}

void Font::font_color(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
{
    m_color.r = r;
    m_color.b = g;
    m_color.g = b;
    m_color.a = a;
}

void Font::font_color(u_int8_t colors[3])
{
    m_color.r = colors[0];
    m_color.b = colors[1];
    m_color.g = colors[2];
    m_color.a = colors[3];
}

