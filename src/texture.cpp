#include "texture.hpp"
#include "window.hpp"

Texture::Texture()
{
    m_pTSurface = nullptr;
    m_pTTexture = nullptr;

    image = std::make_shared<Image>();
}

Texture::~Texture()
{
    // To have sure that the things will be freed.
    SDL_FreeSurface(m_pTSurface);
    SDL_DestroyTexture(m_pTTexture);
}

void Texture::load_texture(const std::string &image_path, const int width,
                             const int height, const int coordinate_x,
                             const int coordinate_y)
{
    image_rect.h = height;
    image_rect.w = width;
    image_rect.x = coordinate_x;
    image_rect.y = coordinate_y;

    m_pTSurface = image->load_png(image_path);

    m_pTTexture = SDL_CreateTextureFromSurface(Window::get_renderer(),
                                               m_pTSurface);

    SDL_FreeSurface(m_pTSurface);

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
