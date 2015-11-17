/* This class is just a prototype, not ready yet.
 *
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

#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "ball.hpp"
#include "paddle.hpp"
#include "window.hpp"
#include "font.hpp"
#include "audio.hpp"
#include "texture.hpp"
#include "random.hpp"

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

    SDL_Event event;

    std::uint32_t current_time;
    // A texture representing the game paused.
    Texture m_pPauseTexture;
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
