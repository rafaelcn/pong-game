/**   Copyright 2014, 2015 Rafael Campos Nunes.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <iostream>
#include <string>
#include <array>

#include <SDL2/SDL.h>

#include "game.hpp"

unsigned int Game::m_fps;
int Game::m_actual_fps;
bool Game::m_is_running;
bool Game::m_pause;
bool Game::debug_mode;
std::shared_ptr<Audio> Game::audio;

Game::Game()
{
    m_fps = 60;
    m_pause = false;
    m_is_running = true;
    debug_mode = false;

    std::string paddle("res/icons/paddle.bmp");
    std::string ball("res/icons/ball.png");

    window = std::make_shared<Window>("Pong Game - Alpha 0.9.1", 800, 600,
                                           SDL_WINDOW_SHOWN);

    image = std::make_shared<Image>();
    audio = std::make_shared<Audio>();


    players_score.font1_rect.h = 120;
    players_score.font1_rect.w = 50;
    players_score.font1_rect.x = Window::get_width()/2-200;
    players_score.font1_rect.y = Window::get_height()/2-230;

    players_score.font2_rect.h = 120;
    players_score.font2_rect.w = 50;
    players_score.font2_rect.x = Window::get_width()/2+150;
    players_score.font2_rect.y = Window::get_height()/2-230;

    players_score.font_player1 = std::make_shared<Font>(
                players_score.font1_rect);

    players_score.font_player2 = std::make_shared<Font>(
                players_score.font2_rect);

    players_score.font_player1->open_font(Font::FontType::font_bold, 400);
    players_score.font_player2->open_font(Font::FontType::font_bold, 400);

    std::array<std::uint8_t, 4> colors = { 200, 200, 200, 255 };

    players_score.font_player1->font_color(colors);
    players_score.font_player2->font_color(colors);

    debug_info.font_debug_rect.h = 30;
    debug_info.font_debug_rect.w = 30;
    debug_info.font_debug_rect.x = (Window::get_width() - 40);
    debug_info.font_debug_rect.y = 10;

    debug_info.font_debug = std::make_shared<Font>(debug_info.font_debug_rect);
    debug_info.font_debug->open_font(Font::FontType::font_normal, 300);
    debug_info.font_debug->font_color(colors);

    //  Creating and loading all game entities.
    player1 = std::make_shared<Paddle>(image->load_bmp(paddle), 1,
                                       Window::get_height()/2-(50/2));

    player2 = std::make_shared<Paddle>(image->load_bmp(paddle),
                                            Window::get_width()-11,
                                            Window::get_height()/2-(50/2));

    this->ball = std::make_shared<Ball>(image->load_png(ball),
                                        Window::get_width()/2,
                                        Window::get_height()/2);

    m_pause_backgroud_texture = std::make_shared<Texture>();
    m_pause_texture = std::make_shared<Texture>();

    m_pause_backgroud_texture->load_texture("res/icons/pause-background.png",
                                           800, 600, 0, 0);

    m_pause_texture->load_texture("res/icons/pause.png", 188, 34,
                                       Window::get_width()/2-(188/2),
                                       Window::get_height()/2-(34/2));
}

Game::~Game()
{
}

void Game::update_game()
{
    current_time = SDL_GetTicks();

    ball->move(player1->get_rect(), player2->get_rect());
    update_game_state();

    if(1000/get_fps() > (SDL_GetTicks() - current_time))
    {
        m_actual_fps = 1000/get_fps()-(SDL_GetTicks() - current_time);

        SDL_Delay(m_actual_fps);
    }
}

void Game::handle_events()
{
    player1->key_state = SDL_GetKeyboardState(nullptr);
    player2->key_state = SDL_GetKeyboardState(nullptr);

    /* SDL_GetKeyboardState it's async. that solved the problem of the paddles
     * moving at the same time.
     * Thanks to veQue on IRC!
     */
    if(player1->key_state[SDL_SCANCODE_W]) {
        player1->move_up();
    }
    if(player1->key_state[SDL_SCANCODE_S]) {
        player1->move_down();
    }
    if(player2->key_state[SDL_SCANCODE_UP]) {
        player2->move_up();
    }
    if(player2->key_state[SDL_SCANCODE_DOWN]) {
        player2->move_down();
    }

    while(SDL_PollEvent(&event)) {
        switch(event.type) {

        case SDL_QUIT:
            Debug::log("SDL has quit normally.");
            m_is_running = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {

            case SDLK_ESCAPE:
                Debug::log("SDL has quit normally.");
                m_is_running = false;
                break;

            case SDLK_r:
                // reset the game.
                restart_game();
                break;

            case SDLK_F5:
                // active debug mode.
                debug_mode = !debug_mode;
                break;

            // activate full screen mode.
            case SDLK_F11:
            {
                int fullscreenFlag = \
                        SDL_GetWindowFlags(Window::get_window());

                if((fullscreenFlag & SDL_WINDOW_FULLSCREEN) ==
                        SDL_WINDOW_FULLSCREEN)
                    SDL_SetWindowFullscreen(Window::get_window(),
                                            0);
                else
                    SDL_SetWindowFullscreen(Window::get_window(),
                                            SDL_WINDOW_FULLSCREEN);
                break;
            }

            case SDLK_p:
                // pause game.
                pause();
                break;
            }
        }
    }
}

void Game::render_game()
{
    SDL_RenderClear(Window::get_renderer());

    player1->show();
    player2->show();
    ball->show();
    render_score();

    if (debug_mode) {
        debug_info.font_debug->render_text_solid(std::to_string(m_actual_fps));
    }

    if (m_pause)
    {
          m_pause_texture->show();
          m_pause_backgroud_texture->show();
    }
    SDL_RenderPresent(Window::get_renderer());
}

/**
 * @brief Pong::renderScore This function renders the score of the game on the
 * screen.
 */
void Game::render_score()
{
    players_score.font_player1->render_text_solid(
                std::to_string(player1->score()));
    players_score.font_player2->render_text_solid(
                std::to_string(player2->score()));
}

bool Game::is_running()
{
    return m_is_running;
}

unsigned int Game::get_fps()
{
    return  m_fps;
}

void Game::pause()
{
    if(!m_pause)
    {
        ball->velocity_x(0.0);
        ball->velocity_y(0.0);
        player1->velocity_y(0.0);
        player2->velocity_y(0.0);
        m_pause = true;

    }
    else
    {
        ball->velocity_x(ball->m_last_ball_speed.x());
        ball->velocity_y(ball->m_last_ball_speed.y());
        player1->velocity_y(6.0);
        player2->velocity_y(6.0);
        m_pause = false;
    }
}

void Game::update_game_state()
{
    SDL_Rect* ball_rect = ball->get_rect();

    if(ball_rect->x+ball_rect->w > Window::get_width())
    {
        player1->add_score();
        reset_game();
        Debug::log("Player 1 score: ", player1->score());
    }
    if(ball_rect->x+ball_rect->w < 0)
    {
        player2->add_score();
        reset_game();
        Debug::log("Player 2 score: ", player2->score());
    }
}

void Game::reset_game()
{
    SDL_Rect* ball_rect = ball->get_rect();

    SDL_Rect* player1_rect = player1->get_rect();
    SDL_Rect* player2_rect = player2->get_rect();

    // Reseting hits on the paddle
    Paddle::reset_hit_count();

    ball->velocity_x(ball->get_random_pos(-5, 5));
    ball->velocity_y(ball->get_random_pos(-3, 3));
    ball_rect->x = Window::get_width()/2-(ball_rect->w);
    ball_rect->y = Window::get_height()/2-(ball_rect->h);

    // Reseting the paddles to default position
    player1_rect->y = Window::get_height()/2-(player1_rect->h/2);
    player2_rect->y = Window::get_height()/2-(player2_rect->h/2);
}

void Game::restart_game()
{
    // TODO: Ball with a minimum speed at spawn.
    // Restarting the game score
    player1->reset_score();
    player2->reset_score();

    reset_game();
}
