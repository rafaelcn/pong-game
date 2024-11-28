#pragma once

#include <array>
#include <memory>

#include <SDL2/SDL.h>

#include "graphics/window.hpp"
#include "math/vector2d.hpp"

/**
 * @brief The Ball class abstracts the ball entity.
 */
class Ball {
private:
  // An array describing the size of the ball, index 0 is width and the 1 is the height
  std::array<int, 2> m_ball_size;

  // The current ball speed.
  Vector2D m_ball_speed;
  
  // The texture of the ball (ball.bmp).
  SDL_Texture* m_texture;
  //SDL_Rect that will represent the size and position of the ball on the screen.
  SDL_Rect m_rect;

  std::shared_ptr<Window> m_window;
private:
  void increase_speed();
  /**
   * @brief Computes if the ball has collided with the given rectangle
   * @param rectangle The rectangle we wanna to test the collision.
   * @return If a collision occurs or not.
   */
  bool collide(SDL_Rect *rectangle);
  void handle_collision(SDL_Rect *player);
public:
  /**
   * @brief Is the variable used when pause game is toggled, it stores
   * the last speed with the ball.
   */
  Vector2D m_last_ball_speed;

public:
  /**
   * @brief The implementation of the class Ball.
   * @param window The root window of the application 
   * @param image The surface that carries the image of the ball.
   * @param x The start position of the ball in the x axis
   * @param y The start position of the ball in the y axis
   */
  Ball(std::shared_ptr<Window> window, SDL_Surface* ball_surface, const float x, const float y);
  ~Ball();

  /**
   * @brief Called to render the ball in the screen.
   */
  void render();
  /**
   * @brief
   */
  void move(SDL_Rect* player1, SDL_Rect* player2);

  /**
   * @brief Ball::velocity A function that returns a Vector2D representing its
   * velocity.
   * @return The velocity as a Vector2D.
   */
  Vector2D velocity();
  /**
   * @brief Ball::velocity_x A function to get the velocity of the ball on the
   * X axis.
   * @return the velocity of the ball on the X axis.
   */
  float velocity_x();
  /**
   * @brief Ball::velocity_y A function to get the velocity of the ball on the
   * Y axis.
   * @return the velocity of the ball on the Y axis.
   */
  float velocity_y();

  /**
   * @brief computes a random value to be used as speed vector for the ball
   * whenever the game resets
   * @param a the range of the random generator.
   * @param b the range of the random generator.
   * @return a random float.
   */
  float get_random_pos(float a, float b);

  /**
   * @brief Ball::velocity_x Function to set the velocity on the X axis of the
   * ball.
   * @param x_velocity The velocity on X axis.
   */
  void velocity_x(float velocity_x);
  /**
   * @brief Ball::velocity_y Function to set the velocity on the Y axis of the
   * ball.
   * @param velocity_y The velocity on Y axis.
   */
  void velocity_y(float velocity_y);

  /**
   * @brief Ball::get_rect() Function to return the SDL_Rect* of the ball.
   * @return A pointer to the ballRect.
   */
  SDL_Rect* get_rect();
};
