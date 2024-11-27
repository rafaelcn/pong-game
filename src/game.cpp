#include <cstdint>
#include <string>
#include <array>

#include <SDL2/SDL.h>

#include "game.hpp"
#include "resources.hpp"

#include "graphics/window.hpp"
#include "graphics/image_manager.hpp"

std::shared_ptr<Audio> Game::audio;

Game::Game()
{
  m_pause = false;
  m_target_fps = 60;
  debug_mode = false;
  m_is_running = true;

  window = std::make_shared<Window>("Pong Game - Alpha 0.9.7", 800, 600, SDL_WINDOW_SHOWN);

  image = std::make_shared<ImageManager>();
  audio = std::make_shared<Audio>();

  players_score.font1_rect.h = 120;
  players_score.font1_rect.w = 50;
  players_score.font1_rect.x = window->get_width()/2-200;
  players_score.font1_rect.y = window->get_height()/2-230;

  players_score.font2_rect.h = 120;
  players_score.font2_rect.w = 50;
  players_score.font2_rect.x = window->get_width()/2+150;
  players_score.font2_rect.y = window->get_height()/2-230;
	
  players_score.font_player1 = std::make_shared<Font>(window, players_score.font1_rect);
  players_score.font_player2 = std::make_shared<Font>(window, players_score.font2_rect);

  players_score.font_player1->open_font(Font::FontType::bold, 400);
  players_score.font_player2->open_font(Font::FontType::bold, 400);

  std::array<std::uint8_t, 4> colors = { 200, 200, 200, 255 };

  players_score.font_player1->font_color(colors);
  players_score.font_player2->font_color(colors);

  debug_info.font_debug_rect.h = 30;
  debug_info.font_debug_rect.w = 30;
  debug_info.font_debug_rect.x = (window->get_width() - 40);
  debug_info.font_debug_rect.y = 10;

  debug_info.font_debug = std::make_shared<Font>(window, debug_info.font_debug_rect);
  debug_info.font_debug->open_font(Font::FontType::normal, 300);
  debug_info.font_debug->font_color(colors);

  //  creating and loading all game entities.
  player1 = std::make_shared<Paddle>(window, image->load_bmp(Resources::paddle), 1, window->get_height()/2-(50/2));
  player2 = std::make_shared<Paddle>(window, image->load_bmp(Resources::paddle), window->get_width()-11, window->get_height()/2-(50/2));

  this->ball = std::make_shared<Ball>(window, image->load_png(Resources::ball), window->get_width()/2, window->get_height()/2);

  m_pause_backgroud_texture = std::make_shared<Texture>(window);
  m_pause_texture = std::make_shared<Texture>(window);
  
  m_pause_backgroud_texture->load(image->load_png(Resources::pause_background),
								  800,
								  600,
								  0,
								  0);

  m_pause_texture->load(image->load_png(Resources::pause_message),
						188,
						34,
                        window->get_width()/2-(188/2),
						window->get_height()/2-(34/2));
}

Game::~Game() {}

void Game::run() {
  current_time = SDL_GetTicks();

  update_game();
  handle_events();
  render_game();

  
  auto partition = 1000/m_target_fps;
  auto difference = SDL_GetTicks() - current_time;
  
  if (partition > difference) {
    m_current_fps = partition-difference;
	
    SDL_Delay(m_current_fps);
  }
}

void Game::update_game()
{
  ball->move(player1->get_rect(), player2->get_rect());

  auto ball_rect = ball->get_rect();
  
  if (ball_rect->x+ball_rect->w > window->get_width()) {
    player1->add_score();
	reset_game();
  } else if (ball_rect->x+ball_rect->w < 0) {
    player2->add_score();
	reset_game();
  }
}

void Game::handle_events()
{
  player1->key_state = SDL_GetKeyboardState(nullptr);
  player2->key_state = SDL_GetKeyboardState(nullptr);

  // SDL_GetKeyboardState is asynchronous
  if (player1->key_state[SDL_SCANCODE_W]) {
    player1->move_up();
  }
  if (player1->key_state[SDL_SCANCODE_S]) {
    player1->move_down();
  }
  if (player2->key_state[SDL_SCANCODE_UP]) {
    player2->move_up();
  }
  if (player2->key_state[SDL_SCANCODE_DOWN]) {
    player2->move_down();
  }

  while (SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_QUIT:
      m_is_running = false;
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        m_is_running = false;
        break;

      case SDLK_r:
        restart_game();
        break;

      case SDLK_F5:
        debug_mode = !debug_mode;
        break;

      case SDLK_F11:
        {
          int window_flags = SDL_GetWindowFlags(window->get_window());
		  bool is_fullscreen = (window_flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN;
			  
          if (is_fullscreen) {
            SDL_SetWindowFullscreen(window->get_window(), 0);
          } else {
            SDL_SetWindowFullscreen(window->get_window(),SDL_WINDOW_FULLSCREEN);
		  }
        }
		break;
		
      case SDLK_p:
        pause();
        break;
      }
    }
  }
}

void Game::render_game()
{
  SDL_RenderClear(window->get_renderer());

  player1->render();
  player2->render();
  ball->render();
  
  render_score();

  if (debug_mode) {
    debug_info.font_debug->render_text_solid(std::to_string(m_current_fps));
  }

  if (m_pause) {
    m_pause_texture->render();
    m_pause_backgroud_texture->render();
  }
  
  SDL_RenderPresent(window->get_renderer());
}

/**
 * @brief Pong::renderScore This function renders the score of the game on the
 * screen.
 */
void Game::render_score()
{
  players_score.font_player1->render_text_solid(std::to_string(player1->score()));
  players_score.font_player2->render_text_solid(std::to_string(player2->score()));
}

bool Game::is_running()
{
  return m_is_running;
}

void Game::pause()
{
  if (!m_pause) {
    ball->velocity_x(0.0);
    ball->velocity_y(0.0);
    player1->velocity_y(0.0);
    player2->velocity_y(0.0);
    m_pause = true;
  } else {
    ball->velocity_x(ball->m_last_ball_speed.x());
    ball->velocity_y(ball->m_last_ball_speed.y());
    player1->velocity_y(6.0);
    player2->velocity_y(6.0);
    m_pause = false;
  }
}

void Game::reset_game()
{
  auto ball_rect = ball->get_rect();

  auto player1_rect = player1->get_rect();
  auto player2_rect = player2->get_rect();

  Paddle::reset_hit_count();

  ball->velocity_x(ball->get_random_pos(-5, 5));
  ball->velocity_y(ball->get_random_pos(-3, 3));

  ball->m_last_ball_speed = ball->velocity();

  ball_rect->x = window->get_width()/2-(ball_rect->w);
  ball_rect->y = window->get_height()/2-(ball_rect->h);

  player1_rect->y = window->get_height()/2-(player1_rect->h/2);
  player2_rect->y = window->get_height()/2-(player2_rect->h/2);
}

void Game::restart_game()
{
  player1->reset_score();
  player2->reset_score();

  reset_game();
}
