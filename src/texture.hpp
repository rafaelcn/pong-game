#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

#include <SDL2/SDL.h>

class Texture {
private:
    //
    SDL_Surface* m_pTSurface;
    //
    SDL_Texture* m_pTTexture;
    //
    SDL_Rect image_rect;
public:
    Texture();
    ~Texture();

    void render_texture(const std::string& image_path, const int width,
                        const int height, const int coordinate_x,
                        const int coordinate_y);
};

#endif // TEXTURE_HPP
