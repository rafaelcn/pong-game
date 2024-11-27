#include <memory>

#include "texture.hpp"
#include "debug.hpp"

Texture::Texture(std::shared_ptr<Window> window)
{
  m_window = window;
  m_texture = nullptr;
}

Texture::~Texture()
{
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
  }
}

void Texture::load(SDL_Surface* image_surface, const int width, const int height, const int x, const int y)
{
  m_rect.h = height;
  m_rect.w = width;
  m_rect.x = x;
  m_rect.y = y;
  
  m_texture = SDL_CreateTextureFromSurface(m_window->get_renderer(), image_surface);
  
  if (m_texture == nullptr) {
    Debug::log_err("failed to create image texture, reason: ", SDL_GetError());
  }

  SDL_FreeSurface(image_surface);
}

void Texture::render()
{
  if (m_texture == nullptr) {
    Debug::log_err("image texture is null");
  } else {
    SDL_RenderCopy(m_window->get_renderer(), m_texture, nullptr, &m_rect);
  }
}
