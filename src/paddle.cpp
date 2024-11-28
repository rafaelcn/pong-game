#include <memory>

#include "paddle.hpp"
#include "debug.hpp"
#include "game.hpp"

int Paddle::m_hits;

Paddle::Paddle(std::shared_ptr<Window> window, SDL_Surface* paddle_image, const float x, const float y)
{
  if(paddle_image == nullptr) {
    Debug::log_err("the paddle image is null");
  } else {
    m_score = 0;

    m_surface        = paddle_image;
    m_rect.x         = x;
    m_rect.y         = y;
    m_rect.w         = paddle_characteristics.width;
    m_rect.h         = paddle_characteristics.height;

	m_window = window;

    m_texture = SDL_CreateTextureFromSurface(m_window->get_renderer(), paddle_image);

    if (m_texture == nullptr) {
      Debug::log_err("failed to create paddle texture!", SDL_GetError());
    }

    SDL_FreeSurface(paddle_image);
  }
}

Paddle::~Paddle()
{
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
  }
}

void Paddle::render()
{
  SDL_RenderCopy(m_window->get_renderer(), m_texture, nullptr, &m_rect);
}

void Paddle::move_up()
{
  /* The minus sign it's because the top left corner of the screen  is like
   * (0,0), so we have to subtract the value  of the  paddleRect->y  by the
   * y velocity.
   * The if statement there is because due the bug of the paddle going out of
   * the screen, I'm limiting the up movement of the paddle by doing the
   * following statement.
   */
  if (m_rect.y > 0) {
    m_rect.y -=  paddle_characteristics.velocity_y;
  }
}

void Paddle::move_down()
{
  /* Same thing here, but the bottom left corner of the screen is like (0, 1)
   * for (x, y) values, so we have to add (...).
   * The if statement is the same Debug::logic used on moveUp(); but here has a POG.
   */
  if (m_rect.y + m_rect.h < m_window->get_height()) {
    m_rect.y +=  paddle_characteristics.velocity_y;
  }
}

SDL_Rect* Paddle::get_rect()
{
  return &m_rect;
}

double Paddle::velocity()
{
  return paddle_characteristics.velocity;
}

void Paddle::velocity(const double v)
{
  paddle_characteristics.velocity = v;
}

int Paddle::score()
{
  return m_score;
}

void Paddle::reset_score()
{
  m_score = 0;
}

void Paddle::add_score()
{
  if (Game::audio->is_open()) {
    Game::audio->play_effect(Audio::EffectType::score_up);
  }
  m_score++;
}

int Paddle::get_hits()
{
  return m_hits;
}

void Paddle::add_hit()
{
  m_hits += 1;
}

void Paddle::reset_hit_count()
{
  m_hits = 0;
}
