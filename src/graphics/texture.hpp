#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include "window.hpp"

/**
 * @brief This class is a wrapper arount the SDL_Texture.
 */
class Texture {
private:
  // A raw pointer to a SDL_Texture struct, it represents the actual texture.
  SDL_Texture* m_texture;
  // Position and size of the texture on the renderer.
  SDL_Rect m_rect;

  std::shared_ptr<Window> m_window;
public:
  Texture(std::shared_ptr<Window> window);
  ~Texture();

  /**
   * @brief load Create a texture from a SDL_Surface struct.
   * @param image_surface The surface containing the image.
   * @param width The width of the texture.
   * @param height The height of the texture.
   * @param x The location of the texture on the x axis.
   * @param y The location of the texture on the y axis.
   */
  void load(SDL_Surface* image_surface, const int width, const int height, const int x, const int y);

  /**
   * @brief renders the texture on the screen
   */
  void render();
};
