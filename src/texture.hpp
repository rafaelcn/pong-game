/*
 * Pong Game.
 * Author: Rafael Campos Nunes.
 * License: Apache v2.
 *
 * Fell free to contact me on
 * Email: rafaelnunes737@hotmail.com
 * Github: https://github.com/rafaelcn
 *
 * Also you can contact me on IRC(freenode.net server) my nickname is: ranu.
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "image.hpp"

/**
 * @brief This class is a wrapper the SDL_Texture and also offers a set of
 * functions.
 */
class Texture {
private:
    //
    SDL_Surface* m_pTSurface;
    //
    SDL_Texture* m_pTTexture;
    //
    SDL_Rect image_rect;
    //
    std::shared_ptr<Image> image;
public:
    Texture();
    ~Texture();
    
    /**
     * @brief
     * 
     */
    void load_texture(const std::string& image_path, const int width,
                        const int height, const int coordinate_x,
                        const int coordinate_y);

    /**
     * @brief
     */
    void show();
};

#endif // TEXTURE_HPP
