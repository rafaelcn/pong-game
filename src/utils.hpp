/*
 * Game: Pong Game.
 * Author: Rafael Campos Nunes.
 * License: Apache v2.
 *
 * Fell free to contact me on
 * Email: rafaelnunes737@hotmail.com
 * Github: https://github.com/rafaelcn
 *
 * Also you can contact me on IRC(freenode.net server) my nickname is: ranu.
 */

#include <SDL2/SDL.h>
#include <iostream>
#include <stdint.h>

#ifndef UTILS_HPP
#define UTILS_HPP

/**
  * @brief loadBMP A function to load BMP images and then return a pointer
  * to the surface that contains the image.
  * @param path the path to where the image is located.
  * @param colorKey the color key of the image.
  * @return a pointer to a surface which contains the image.
  */
SDL_Surface* loadBMP(std::string path, int32_t colorKey[3]);

/**
 * @brief loadBMP A function to load BMP images and then return a pointer
 * to the surface that contains the image.
 * @param path path the path to where the image is located.
 * @return a pointer to a surface which contains the image.
 */
SDL_Surface* loadBMP(std::string path);

//not ready yet, memory leak and other stuff.
void renderTexture(SDL_Surface* surface, SDL_Renderer** renderer,
                   int width, int height, int xCord, int yCord);

#endif
