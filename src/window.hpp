/**
 * Copyright 2014-2018 Rafael Campos Nunes.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain a
 * copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstdint>
#include <iostream>
#include <array>

#include <SDL2/SDL.h>

#include "debug.hpp"

/**
 * @brief Class which has all the resources to create a window for the game
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
     * @return The renderer of the game window.
     */
    static SDL_Renderer* get_renderer();

    /**
     * @brief get_width
     * @return The width of the game window.
     */
    static int get_width();
    /**
     * @brief get_height
     * @return The height of the game window.
     */
    static int get_height();
};

#endif // WINDOW_HPP
