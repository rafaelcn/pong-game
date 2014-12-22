#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class FontManager
{
private:
    //
    TTF_Font* m_pFont;
    //
    SDL_Color m_color;

public:
    FontManager();
    ~FontManager();
};

#endif // FONTMANAGER_HPP
