#include <iostream>
#include <string>
#include <memory>
#include <array>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "game.hpp"
#include "debug.hpp"
#include "utils.hpp"

unsigned int Game::m_fps;
bool Game::m_is_running;
bool Game::m_pause;
bool Game::debug_mode;

/**
 * @brief Pong::Pong
 */
Game::Game()
{
    m_fps = 60;
    m_pause = false;
    m_is_running = true;
    debug_mode = false;

    std::string paddle("res/icons/paddle.bmp");
    std::string ball("res/icons/ball.bmp");

    window = std::make_shared<Window>("Pong Game", 800, 600,
                                           SDL_WINDOW_SHOWN);

    player1 = std::make_shared<Paddle>(Utils::load_bmp(paddle), 1,
                                       Window::get_height()/2-(50/2));

    player2 = std::make_shared<Paddle>(Utils::load_bmp(paddle),
                                            Window::get_width()-12,
                                            Window::get_height()/2-(50/2));

    this->ball = std::make_shared<Ball>(Utils::load_bmp(ball),
                                        Window::get_width()/2,
                                        Window::get_height()/2);

    audio = std::make_shared<Audio>(game_audio.hit_paddle_effect,
                                    game_audio.game_music);

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
        int delay_time = 1000/get_fps()-(SDL_GetTicks() - current_time);

        if(debug_mode)
        {
            // Display the delay time on the screen.
        }

        SDL_Delay(delay_time);
    }
}

void Game::handle_events()
{
    player1->paddle_moviment.key_state = SDL_GetKeyboardState(nullptr);
    player2->paddle_moviment.key_state = SDL_GetKeyboardState(nullptr);

    /* SDL_GetKeyboardState it's async. that solved the problem of the paddles
     * moving at the same time.
     * Thanks to veQue on IRC!
     */
    if(player1->paddle_moviment.key_state[SDL_SCANCODE_W]) {
        player1->paddle_moviment.player_keys[0] = true;
    }
    if(player1->paddle_moviment.key_state[SDL_SCANCODE_S]) {
        player1->paddle_moviment.player_keys[1] = true;
    }
    if(player2->paddle_moviment.key_state[SDL_SCANCODE_UP]) {
        player2->paddle_moviment.player_keys[0] = true;
    }
    if(player2->paddle_moviment.key_state[SDL_SCANCODE_DOWN]) {
        player2->paddle_moviment.player_keys[1] = true;
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
                // active debug stuff.
                if(debug_mode) { debug_mode = false; }
                else {debug_mode = true; }
                break;

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
                //pause game stuff
                pause();
                break;
            }
        }
    }

    if(player1->paddle_moviment.player_keys[0]) {
        player1->move_up();
    }
    if(player1->paddle_moviment.player_keys[1]) {
        player1->move_down();
    }
    if(player2->paddle_moviment.player_keys[0]) {
        player2->move_up();
    }
    if(player2->paddle_moviment.player_keys[1]) {
        player2->move_down();
    }

    for(int i = 0; i < 2; i++) {
        player1->paddle_moviment.player_keys[i] = false;
        player2->paddle_moviment.player_keys[i] = false;
    }
}

void Game::render_game()
{
    SDL_RenderClear(Window::get_renderer());

    player1->show();
    player2->show();
    ball->show();
    render_score();

    if(m_pause)
    {
        game_paused.render_texture("res/icons/pause.bmp", 188, 34,
                                   Window::get_width()/2-(188/2),
                                   Window::get_height()/2-(34/2));

        game_paused.render_texture("res/icons/pause-background.bmp", 800, 600,
                                   0, 0);
    }

    SDL_RenderPresent(Window::get_renderer());
}

/**
 * @brief Pong::renderScore This function renders the score of the game on the
 * screen.
 */
void Game::render_score()
{
    std::string player1_score = std::to_string(player1->score());
    std::string player2_score = std::to_string(player2->score());

    players_score.font_player1->render_text_solid(player1_score);
    players_score.font_player2->render_text_solid(player2_score);
}

bool Game::is_running()
{
    return m_is_running;
}

/**
 * @brief Pong::getFPS A function to get the desired FPS for the game.
 * @return the desired FPS for the game.
 */
unsigned int Game::get_fps()
{
    return  m_fps;
}

/**
 * @brief Pong::pauseGame is a function to pause the game.
 */
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
        ball->velocity_x(ball->last_ball_speed.x());
        ball->velocity_y(ball->last_ball_speed.y());
        player1->velocity_y(6.0);
        player2->velocity_y(6.0);
        m_pause = false;
    }
}

/**
 * @brief Game::update_game_state
 */
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

/**
 * @brief Pong::reset_game is the function which resets the game state, setting
 * back the ball and the paddles position.
 */
void Game::reset_game()
{
    SDL_Rect* ball_rect = ball->get_rect();

    SDL_Rect* player1_rect = player1->get_rect();
    SDL_Rect* player2_rect = player2->get_rect();

    //reseting hits on the paddle
    Paddle::reset_hit_count();

    //Reseting ball to default position and velocity
    ball->velocity_x(3.0f);
    ball->velocity_y(1.0f);
    ball_rect->x = Window::get_width()/2-(ball_rect->w);
    ball_rect->y = Window::get_height()/2-(ball_rect->h);

    //Reseting the paddles to default position
    player1_rect->y = Window::get_height()/2-(player1_rect->h/2);
    player2_rect->y = Window::get_height()/2-(player2_rect->h/2);
}

void Game::restart_game()
{
    // Restarting the game score
    player1->reset_score();
    player2->reset_score();

    reset_game();
}
