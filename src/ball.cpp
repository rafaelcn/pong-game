#include <cmath>
#include <algorithm>
#include <memory>

#include "ball.hpp"
#include "game.hpp"
#include "debug.hpp"

#include "math/random.hpp"

Ball::Ball(std::shared_ptr<Window> window, SDL_Surface* ball_surface, const float x, const float y) :
  m_ball_speed(get_random_pos(-5, 5), get_random_pos(-3, 3)),
  m_last_ball_speed(m_ball_speed)
{
  m_window = window;
  
  if (ball_surface == nullptr) {
    Debug::log_err("ball surface is null, check in the resources folder");
  } else {
    m_ball_size[0] = 10;
    m_ball_size[1] = 10;
	
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = m_ball_size[0];
    m_rect.h = m_ball_size[1];
	
    m_texture = SDL_CreateTextureFromSurface(m_window->get_renderer(), ball_surface);
	
    if (m_texture == nullptr) {
      Debug::log_err("failed to create ball texture, reason ", SDL_GetError());
    }

    SDL_FreeSurface(ball_surface);
  }
}

Ball::~Ball()
{
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
  }
}

void Ball::render()
{
  SDL_RenderCopy(m_window->get_renderer(), m_texture, nullptr, &m_rect);
}


void Ball::move(SDL_Rect* player1, SDL_Rect* player2)
{
  m_rect.x += velocity_x();
  m_rect.y += velocity_y();
  
  // detecting the collision on the Y axis.
  if (m_rect.y <= 0 || m_rect.y+m_rect.h > m_window->get_height()) {
    velocity_y(-m_ball_speed.y());
    m_last_ball_speed = m_ball_speed;
  }

  handle_collision(player1);
  handle_collision(player2);
}

void Ball::handle_collision(SDL_Rect* player)
{
  if (collide(player)) {
	if (Paddle::get_hits() == 3) {
      increase_speed();
      velocity_x(-m_ball_speed.x());
      Paddle::reset_hit_count();
    } else {
      velocity_x(-m_ball_speed.x());
    }

	m_last_ball_speed = m_ball_speed;
	
	if (Game::audio->is_open()) {
      Game::audio->play_effect(Audio::EffectType::hit_paddle);
	}
	
	Paddle::add_hit();
	
	Debug::log("hit count: ", Paddle::get_hits());
  }
}

bool Ball::collide(SDL_Rect* rectangle)
{
  // AABB
  if (m_rect.y >= rectangle->y + rectangle->h) {
    return false;
  }
  if (m_rect.x >= rectangle->x + rectangle->w) {
    return false;
  }
  if (m_rect.y + m_rect.h <= rectangle->y) {
    return false;
  }
  if (m_rect.x + m_rect.w <= rectangle->x) {
    return false;
  }
	
  return true;
}

void Ball::increase_speed()
{
  Vector2D max_speed(8., 6.);
	
  auto increase = m_ball_speed() + m_ball_speed() * Random::get_real(0.1f, 0.15f);
  auto speed = std::min(increase.magnitude(), max_speed.magnitude());
  
  if (velocity_x() < 0.0f) {
	velocity_x(-speed);
  }  else {
	velocity_x(speed);
  }

  Debug::log("New speed is: x(", velocity_x(), ") y(", velocity_y(), ")");
}

SDL_Rect* Ball::get_rect()
{
  return &m_rect;
}

float Ball::velocity_x()
{
  return m_ball_speed.x();
}

float Ball::velocity_y()
{
  return m_ball_speed.y();
}

float Ball::get_random_pos(float a, float b)
{
  float value;

  // conditional loop created to not receive a low value.
  do {
    value = Random::get_real(a, b);
  } while (value >= -2.0f && value <= 3.0f);
  
  return value;
}

void Ball::velocity_x(float velocity_x)
{
  m_ball_speed.x(velocity_x);
}

void Ball::velocity_y(float velocity_y)
{
  m_ball_speed.y(velocity_y);
}
