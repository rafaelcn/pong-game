/**
 * Copyright 2014 Rafael Campos Nunes.
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

#include "window.hpp"

SDL_Window* Window::m_pWindow;
SDL_Renderer* Window::m_pRenderer;

std::array<int, 2> Window::m_window_size;

Window::Window(const std::string& title, int width, int height,
               std::uint32_t flags)
{
    m_pWindow = nullptr;
    m_pRenderer = nullptr;


    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        Debug::log_err("Couldn't initialize the video | audio.", SDL_GetError());
    }
    else
    {
        Debug::log("SDL Initialized.");
        m_pWindow = SDL_CreateWindow(title.c_str(),
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           width,
                                           height,
                                           flags);

        m_window_size[0] = width;
        m_window_size[1] = height;


        if(m_pWindow == nullptr)
        {
            Debug::log_err("Window couldn't be created.", SDL_GetError());
        }
        else
        {
            SDL_ShowCursor(0); //don't show the cursor.

            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1,
                                             SDL_RENDERER_ACCELERATED |
                                             SDL_RENDERER_PRESENTVSYNC);

            if(m_pRenderer == nullptr)
            {
                Debug::log_err("Window renderer couldn't be created.",
                              SDL_GetError());
            }
            else {
                SDL_SetRenderDrawColor(m_pRenderer, 0x20, 0x20, 0x20, 1);
            }
        }
    }
}

Window::~Window()
{
    if(m_pRenderer != nullptr) {
        SDL_DestroyRenderer(m_pRenderer);
    }
    if(m_pWindow != nullptr) {
        SDL_DestroyWindow(m_pWindow);
    }
}


SDL_Window* Window::get_window()
{
   return m_pWindow;
}

SDL_Renderer* Window::get_renderer()
{
    return m_pRenderer;
}

int Window::get_width()
{
    return m_window_size[0];
}

int Window::get_height()
{
    return m_window_size[1];
}
