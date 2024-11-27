#include "image_manager.hpp"
#include "debug.hpp"

#include <SDL2/SDL_image.h>
#include <exception>

bool ImageManager::m_image_opened = false;

ImageManager::ImageManager()
{
  if (!m_image_opened) {
    if (IMG_Init(IMG_INIT_PNG) == 0) {
      Debug::log_err("failed to initialize image subsystem, reason:", SDL_GetError());
	  return;
    }
	
    Debug::log("image subsystem initialized.");
	
    m_image_opened = true;
  }
}

ImageManager::~ImageManager() {
  if (m_image_opened) {
	IMG_Quit();
  }
}

SDL_Surface* ImageManager::load_bmp(const std::string& path, int color_key_state, const std::array<std::uint32_t, 3>& color_key)
{
  SDL_Surface* image = SDL_LoadBMP(path.c_str());
  
  if (image == nullptr) {
    Debug::log_err("failed to load image ", path,", reason ", SDL_GetError());
  }
  else {
    SDL_SetColorKey(image,
					color_key_state,
					SDL_MapRGB(
							   image->format,
							   color_key[0], color_key[1], color_key[2]
							   )
					);
  }
  
  return image;
}

SDL_Surface* ImageManager::load_bmp(const std::string &path, const std::array<std::uint32_t, 3>& color_key)
{
  return load_bmp(path, SDL_TRUE, color_key);
}

SDL_Surface* ImageManager::load_bmp(const std::string &path)
{
  std::array<std::uint32_t, 3> color_key_{{ 0, 0, 0 }};
  
  return load_bmp(path, SDL_FALSE, color_key_);
}

SDL_Surface* ImageManager::load_png(const std::string &path)
{
  SDL_Surface* image = nullptr;
  SDL_RWops* rwop = nullptr;
  
  if (m_image_opened) {
    rwop = SDL_RWFromFile(path.c_str(), "rb");
    image = IMG_LoadPNG_RW(rwop);
  }

  if (image == nullptr) {
    Debug::log_err("failed to load image ", path,", reason ", SDL_GetError());
  }
  
  return image;
}
