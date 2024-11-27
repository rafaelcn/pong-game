#include "font_manager.hpp"
#include "debug.hpp"

bool FontManager::m_ttf_opened = false;

FontManager::FontManager()
{
  m_font = nullptr;

  m_color.r = 0xff;
  m_color.b = 0xff;
  m_color.g = 0xff;
  m_color.a = 1;
  
  m_color_shaded.r = 0x00;
  m_color_shaded.b = 0x00;
  m_color_shaded.g = 0x00;
  m_color_shaded.a = 1;

  if (!m_ttf_opened) {
	// FIXME: this code is being called for every font object present on the system
	// and we should have only one instance of the font manager.
	if (TTF_Init() != 0) {
      Debug::log_err("failed to initialize the font system", SDL_GetError());
	  return;
	}

	m_ttf_opened = true;
	
	Debug::log("font subsystem initialized");
  }
}

FontManager::~FontManager()
{
  TTF_Quit();
}
