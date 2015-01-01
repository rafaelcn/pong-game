#include "texture.hpp"
#include "window.hpp"
#include "utils.hpp"

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

void Texture::render_texture(const std::string &image_path, const int width,
                             const int height, const int coordinate_x,
                             const int coordinate_y)
{
    SDL_Renderer* renderer = Window::get_renderer();

    image_rect.h = height;
    image_rect.w = width;
    image_rect.x = coordinate_x;
    image_rect.y = coordinate_y;

    m_pTSurface = Utils::load_bmp(image_path);

    m_pTTexture = SDL_CreateTextureFromSurface(renderer, m_pTSurface);

    SDL_FreeSurface(m_pTSurface);

    if(m_pTTexture == nullptr)
    {
        Debug::logerr("Image texture is null! error: ", SDL_GetError());
    }
    else
    {
        SDL_RenderCopy(renderer, m_pTTexture, nullptr, &image_rect);

        SDL_DestroyTexture(m_pTTexture);
    }
}
