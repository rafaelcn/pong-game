#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <stdint.h>

#include <SDL2/SDL.h>

#include "debug.hpp"

class Window
{
private:
    // Private default constructor. I could write Window() = delete; as well.
    Window();
    // The main window of the game.
    static SDL_Window* m_pWindow;
    // The main renderer of the window, which will be the background.
    static SDL_Renderer* m_pRenderer;
    // Array describing the window size (width, height)
    static int m_window_size[2];

public:
    /**
     * @brief Window
     * @param title
     * @param width
     * @param height
     * @param flags
     */
    Window(const std::string& title, int width, int height, uint32_t flags);
    ~Window();

    /**
     * @brief get_window
     * @return
     */
    static SDL_Window* get_window();
    /**
     * @brief get_renderer
     * @return
     */
    static SDL_Renderer* get_renderer();

    /**
     * @brief get_width
     * @return
     */
    static int get_width();
    /**
     * @brief get_height
     * @return
     */
    static int get_height();


};

#endif // WINDOW_HPP
