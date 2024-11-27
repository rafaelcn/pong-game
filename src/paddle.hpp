#pragma once

#include <cstdint>
#include <memory>

#include <SDL2/SDL.h>

#include "graphics/window.hpp"

/**
 * @brief The Paddle class abstracts the paddle entity.
 */
class Paddle {
private:
  /**
   * @brief The paddle_characteristcs struct is the container of almost all
   * characteristics like it velocity, width and height.
   */
  struct paddle_characteristics {
    float velocity_y    = 6.0f;
    int width           = 10;
    int height          = 50;
  } paddle_characteristics;

  // Hit counter used to speed up the ball.
  static int m_hits;
  //Score of the paddle (player)
  int m_score;
  //The image of the paddle that will be loaded on a surface.
  SDL_Surface* m_surface;
  //The paddle itself, it's the texture of the paddleImage.
  SDL_Texture* m_texture;
  //SDL_Rect that will represent the size of the paddle on the screen.
  SDL_Rect m_rect;

  std::shared_ptr<Window> m_window;
public:
  /**
   * @brief Constructor of the class that initializes the values
   * of the private variables with the given parameters for the class.
   * @param paddle_image The surface that carries the image of the paddle.
   * @param x The start position of the paddle in the x axis
   * @param y The start position of the paddle in the y axis
   */
  Paddle(std::shared_ptr<Window> window, SDL_Surface *paddle_image, const float x, const float y);
  ~Paddle();

  /**
   * @brief Returns the actual SDL_Rect* used to represent the
   * paddle.
   * @return The current SDL_Rect* used to represent the paddle
   */
  SDL_Rect* get_rect();

  /**
   * @brief renders the paddle on the screen
   */
  void render();
  /**
   * @brief move_up Moves the paddle up.
   */
  void move_up();
  /**
   * @brief move_down Moves the paddle down.
   */
  void move_down();

  /**
   * @brief A getter for the paddle velocity.
   * @return The current velocity on the Y axis.
   */
  double velocity_y();
  /**
   * @brief A setter for the paddle velocity.
   * @param velocity_y The velocity of the paddle on the Y axis.
   */
  void velocity_y(const double velocity_y);

  /**
   * @brief Get the actual score of the player.
   * @return the actual score of the player.
   */
  int score();
  /**
   * @brief add_score Add an score to the paddle.
   */
  void add_score();
  /**
   * @brief add_hit
   */
  static void add_hit();
  /**
   * @brief get_hits get the total number of times that the ball has hitted
   * the paddle.
   * @return an integer representing the number of times that the ball has
   * hitted the paddle.
   */
  static int get_hits();
  /**
   * @brief reset_hit_count Set the number of times that the ball has hitted
   * the paddle to zero.
   */
  static void reset_hit_count();
  /**
   * @brief reset_score set the score of the paddle to zero.
   */
  void reset_score();

  /**
   * @brief The key_state holds the state of the keyboard
   */
  const std::uint8_t* key_state;
};
