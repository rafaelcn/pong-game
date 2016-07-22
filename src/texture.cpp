#include "texture.hpp"
#include "window.hpp"

Texture::Texture()
{
    m_pTSurface = nullptr;
    m_pTTexture = nullptr;
}

Texture::~Texture()
{
    // To have sure that the things will be freed.
    SDL_FreeSurface(m_pTSurface);
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
