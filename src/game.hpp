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

#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "ball.hpp"
#include "paddle.hpp"
#include "window.hpp"
#include "font.hpp"
#include "audio.hpp"
#include "texture.hpp"
#include "random.hpp"
#include "image.hpp"

/**
 * @brief The game class represent the game itself, it wrappers all the other
 * entities and intializes them in order to make the Pong work.
 */
class Game
{
private:
    struct players_score
    {
        // Fonts used to render the score.
        std::shared_ptr<Font> font_player1;
        std::shared_ptr<Font> font_player2;
        // The rect of each font.
        SDL_Rect font1_rect;
        SDL_Rect font2_rect;
    } players_score;

    /**
     * @brief The debug_info struct
     */
    struct debug_info {
        //
        std::shared_ptr<Font> font_debug;
        //
        SDL_Rect font_debug_rect;
    } debug_info;

    SDL_Event event;

    std::uint32_t current_time;
    // A texture representing the game paused.
    std::shared_ptr<Texture> m_pause_texture;
    std::shared_ptr<Texture> m_pause_backgroud_texture;
    // current FPS.
    static int m_actual_fps;
    // The desired FPS for the game.
    static unsigned int m_fps;
    // Represents the state of the game
    static bool m_is_running;
    // If the game is paused or no.
    static bool m_pause;

    // The players.
    std::shared_ptr<Paddle> player1;
    std::shared_ptr<Paddle> player2;
    // The ball
    std::shared_ptr<Ball> ball;
    // The window of the game
    std::shared_ptr<Window> window;
    //
    std::shared_ptr<Image> image;

public:
    // The variable which describes if we are in the debug mode.
    static bool debug_mode;

    // The audio of the game
    static std::shared_ptr<Audio> audio;

public:
    /**
     * @brief Constructor of the game class. It initializes every game entity.
     */
    Game();
    ~Game();

    /**
     * @brief Update all the game logic, such as a paddle movement request, or
     * move the ball.
     */
    void update_game();
    /**
     * @brief Render all the entities of the game.
     */
    void render_game();
    /**
     * @brief Handle all the events of the game, such as key press.
     */
    void handle_events();

    /**
     * @brief Returns the desired FPS for the game.
     * @return An unsigned int as the desired FPS.
     */
    static unsigned int get_fps();

    /**
     * @brief
     * @return A boolean value determining the run state of the game.
     */
    static bool is_running();

    /**
     * @brief Pause and unpause the game, toggling the m_pause variable.
     */
    void pause();
    /**
     * @brief render_score
     */
    void render_score();
    /**
     * @brief update_game_state
     */
    void update_game_state();
    /**
     * @brief Restart the game state, setting values of ball, paddles position
     * and score to default.
     */
    void restart_game();
    /**
     * @brief Reset the game state, i.e. setting the score player values to
     * default and hence the position of entities in the game.
     */
    void reset_game();
};

#endif // GAME_HPP
