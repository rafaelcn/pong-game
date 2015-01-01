/* This class is just a prototype, not ready yet.
 *
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

#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <cstdint>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "ball.hpp"
#include "paddle.hpp"
#include "window.hpp"
#include "font.hpp"
#include "audio.hpp"
#include "texture.hpp"

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
     * @brief The game_audio struct contains all information about the audio
     * used in the game
     */
    struct game_audio
    {
        Mix_Chunk* hit_paddle_effect;
        Mix_Chunk* hit_walls_effect;
        Mix_Chunk* score_up_effect;
        Mix_Music* game_music;
    } game_audio;
    //
    SDL_Event event;
    //
    u_int32_t current_time;
    //
    Texture game_paused;
    // The desired FPS for the game.
    static unsigned int m_fps;
    // Represents the state of the game
    static bool m_is_running;
    // If the game is paused or no.
    static bool m_pause;
    // The audio of the game
    std::shared_ptr<Audio> audio;
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
public:
    Game();
    ~Game();

    void update_game();
    void render_game();
    void handle_events();

    static unsigned int get_fps();

    static bool is_running();
    /**
     * @brief pause
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
     * @brief restart_game
     */
    void restart_game();
    /**
     * @brief reset_game
     */
    void reset_game();
};

#endif // GAME_HPP
