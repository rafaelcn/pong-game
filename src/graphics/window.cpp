#include "window.hpp"
#include "debug.hpp"

Window::Window(const std::string& title, int width, int height, std::uint32_t flags)
{
    m_window = nullptr;
    m_renderer = nullptr;


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
      Debug::log_err("failed to initialize the video or audio, reason", SDL_GetError());
    } else {
        Debug::log("SDL Initialized.");
        m_window = SDL_CreateWindow(title.c_str(),
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           width,
                                           height,
                                           flags);

        m_window_size[0] = width;
        m_window_size[1] = height;


        if(m_window == nullptr) {
          Debug::log_err("failed to create window, reason", SDL_GetError());
        } else {
            SDL_ShowCursor(0); //don't show the cursor.

            m_renderer = SDL_CreateRenderer(m_window, -1,
                                             SDL_RENDERER_ACCELERATED |
                                             SDL_RENDERER_PRESENTVSYNC);

            if(m_renderer == nullptr) {
                Debug::log_err("failed to create window renderer", SDL_GetError());
            } else {
                SDL_SetRenderDrawColor(m_renderer, 0x20, 0x20, 0x20, 1);
            }
        }
    }
}

Window::~Window()
{
    if(m_renderer != nullptr) {
        SDL_DestroyRenderer(m_renderer);
    }
    if(m_window != nullptr) {
        SDL_DestroyWindow(m_window);
    }
}


SDL_Window* Window::get_window()
{
   return m_window;
}

SDL_Renderer* Window::get_renderer()
{
    return m_renderer;
}

int Window::get_width()
{
    return m_window_size[0];
}

int Window::get_height()
{
    return m_window_size[1];
}
