#include <iostream>
#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "game.hpp"
#include "debug.hpp"
#include "window.hpp"
#include "font.hpp"
#include "utils.hpp"

unsigned int Game::m_fps;
bool Game::m_is_running;
bool Game::m_pause;

/**
 * @brief Pong::Pong
 */
Game::Game()
{
    m_fps = 60;
    m_pause = false;
    m_is_running = true;

    // TODO: Take out this from here.
    std::string paddle("res/icons/paddle.bmp");
    std::string ball("res/icons/ball.bmp");
    std::string ballSound("res/sounds/ballHit.wav");
    int32_t ball_color_key[3] = { 0x20, 0x20, 0x20 };

    window = std::make_shared<Window>("Pong Game", 800, 600,
                                           SDL_WINDOW_SHOWN);

    player1 = std::make_shared<Paddle>(Utils::load_bmp(paddle),
                                            1, Window::get_height()/2-(50/2));

    player2 = std::make_shared<Paddle>(Utils::load_bmp(paddle),
                                            Window::get_width()-12,
                                            Window::get_height()/2-(50/2));

    this->ball = std::make_shared<Ball>(Utils::load_bmp(ball, ball_color_key),
                                        Window::get_width()/2,
                                        Window::get_height()/2);



    audio = std::make_shared<Audio>(game_audio.hit_paddle_effect,
                                       game_audio.game_music);

    players_score.player1_rect = new SDL_Rect();
    players_score.player2_rect = new SDL_Rect();

    players_score.player1_rect->h = 120;
    players_score.player1_rect->w = 50;
    players_score.player1_rect->x = Window::get_width()/2-200;
    players_score.player1_rect->y = Window::get_height()/2-230;

    players_score.player2_rect->h = 120;
    players_score.player2_rect->w = 50;
    players_score.player2_rect->x = Window::get_width()/2+150;
    players_score.player2_rect->y = Window::get_height()/2-230;

    players_score.font_player1 = std::make_shared<Font>(
                Window::get_renderer(), players_score.player1_rect);

    players_score.font_player2 = std::make_shared<Font>(
                Window::get_renderer(), players_score.player2_rect);

    players_score.font_player1->open_font(Font::FontType::font_bold, 400);
    players_score.font_player2->open_font(Font::FontType::font_bold, 400);

}

Game::~Game()
{

}

void Game::update_game()
{
    current_time = SDL_GetTicks();

    ball->move(player1->get_rect(), player2->get_rect());
    update_game_state();

    if(1000/get_fps() > (SDL_GetTicks() - current_time)) {
        SDL_Delay(1000/get_fps()-(SDL_GetTicks() - current_time));
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

            case SDLK_ASTERISK:
                // active debug stuff.
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
                //pause();

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
    //memory leak on renderTexture
    //renderTexture(loadBMP(paddle), &windowRenderer, 10,
    //              pong.get_height(), pong.getWidth()/2-(10/2),
    //              0);
    player1->show();
    player2->show();
    ball->show();
    render_score();

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
 * Uow, so much many hacks in this class. >.>
 * @brief Pong::pauseGame A function to pause the game.
 * @param Bll the ball which is on the game.
 * @param player1 The player 1 which is on the game.
 * @param player2 The player 2 which is on the game.
 */
void Game::pause()
{
//    double ball_velocity[2] = { ball->velocity_x(), ball->velocity_y() };

//    if(! m_pause)
//    {
//        ball->velocity_x(0.0);
//        ball->velocity_y(0.0);
//        player1->velocity_y(0.0);
//        player2->velocity_y(0.0);
//        m_pause = true;
//        //TODO: have to render a texture which says: GAME PAUSED!
//    }
//    else
//    {
//        ball->velocity_x(ball_velocity[0]);
//        ball->velocity_y(ball_velocity[1]);
//        player1->velocity_y(6.0);
//        player2->velocity_y(6.0);
//        m_pause = false;
//    }
}

/**
 * @brief Pong::updateGameState Function that sets all components of the game
 * for the default positions.
 * @param player1 A pointer to a paddle which is the player1.
 * @param player2 A pointer to a paddle which is the player2.
 * @param ballObject Pointer that carries the object of the ball.
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
        Debug::log("Player 1 score: ", player2->score());
    }
}

/**
 * @brief Pong::resetGameState The function resets the game state, setting back
 * the ball amd the paddles position.
 * @param player1 A pointer to the player1 object(paddle).
 * @param player2 A pointer to the player2 object(paddle).
 * @param ballObject A pointer to the ball.
 */
void Game::reset_game()
{
    SDL_Rect* ball_rect = ball->get_rect();

    SDL_Rect* player1_rect = player1->get_rect();
    SDL_Rect* player2_rect = player2->get_rect();

    //reseting hits on the paddle
    Paddle::reset_hit_count();

    //Reseting ball to default position and velocity
    ball->velocity_x(2.0);
    ball->velocity_y(1.0);
    ball_rect->x = Window::get_width()/2-(ball_rect->w);
    ball_rect->y = Window::get_height()/2-(ball_rect->h);

    //Reseting the paddles to default position
    player1_rect->y = Window::get_height()/2-(player1_rect->h/2);
    player2_rect->y = Window::get_height()/2-(player2_rect->h/2);
}
