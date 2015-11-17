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

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <array>

#include <SDL2/SDL.h>

#include "debug.hpp"

/**
 * Class which has all the resources to create a window for the game by
 * providing a clear API.
 */
class Window {
private:
    // Private default constructor. I could write Window() = delete; as well.
    Window();
    // The main window of the game.
    static SDL_Window* m_pWindow;
    // The main renderer of the window, which will be the background.
    static SDL_Renderer* m_pRenderer;
    // Array describing the window size (width, height)
    static std::array<int, 2> m_window_size;

public:
    /**
     * @brief Window ctor of the game window.
     * @param title The title of the game window.
     * @param width The width of the game window.
     * @param height The height of the game window.
     * @param flags The flags setted to the game window.
     */
    Window(const std::string& title, int width, int height,
           std::uint32_t flags);
    ~Window();

    /**
     * @brief get_window function that returns the pointer to the
     * @return the game window.
     */
    static SDL_Window* get_window();
    /**
     * @brief get_renderer
     * @return the renderer of the game window.
     */
    static SDL_Renderer* get_renderer();

    /**
     * @brief get_width
     * @return the width of the game window.
     */
    static int get_width();
    /**
     * @brief get_height
     * @return the height of the game window.
     */
    static int get_height();
};

#endif // WINDOW_HPP
