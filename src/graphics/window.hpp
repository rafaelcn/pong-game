#pragma once

#include <cstdint>
#include <string>
#include <array>

#include <SDL2/SDL.h>

/**
 * @brief Class which has all the resources to create a window for the game
 */
class Window {
private:
  Window();
  Window(Window&);
  
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
  
  std::array<int, 2> m_window_size;

public:
    /**
     * @brief Window ctor of the game window.
     * @param title The title of the game window.
     * @param width The width of the game window.
     * @param height The height of the game window.
     * @param flags The flags setted to the game window.
     */
    Window(const std::string& title, int width, int height, std::uint32_t flags);
    ~Window();

    /**
     * @return A pointer to the game window.
     */
    SDL_Window* get_window();
    /**
     * @return A pointer to the renderer of the window.
     */
    SDL_Renderer* get_renderer();

    /**
     * @return The width of the game window.
     */
    int get_width();
    /**
     * @return The height of the game window.
     */
    int get_height();
};
