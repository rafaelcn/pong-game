#pragma once

#include <memory>
#include <cstdint>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "graphics/window.hpp"
#include "graphics/font.hpp"
#include "graphics/texture.hpp"
#include "graphics/image_manager.hpp"

#include "ball.hpp"
#include "paddle.hpp"
#include "audio.hpp"

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
   * @brief Storoes information that will be displayed on debug mode
   */
  struct debug_info {
    std::shared_ptr<Font> font_debug;
    SDL_Rect font_debug_rect;
  } debug_info;

  SDL_Event event;

  std::uint32_t current_time;

  std::shared_ptr<Texture> m_pause_texture;
  std::shared_ptr<Texture> m_pause_backgroud_texture;

  std::uint32_t m_target_fps;
  std::uint32_t m_current_fps;
  
  bool m_is_running;
  bool m_pause;

  std::shared_ptr<Paddle> player1;
  std::shared_ptr<Paddle> player2;
  
  std::shared_ptr<Ball> ball;
  
  std::shared_ptr<Window> window;  
  std::shared_ptr<ImageManager> image;

public:
  // The variable which describes if we are in the debug mode.
  bool debug_mode;

  static std::shared_ptr<Audio> audio;
public:
  /**
   * @brief Constructor of the game class. It initializes every game entity.
   */
  Game();
  ~Game();

  /**
   * @brief
   * @return A boolean value determining the run state of the game.
   */
  bool is_running();

  /**
   * @brief runs the game updating the state, handling events and rendering it
   */
  void run();

private:
  
    /**
   * @brief toggles a variable to pause the game.
   */
  void pause();
  
  /**
   * @brief renders the player's score on the screen
   */
  void render_score();
  
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
  
    /**
   * @brief update all the game logic, such as a paddle movement request, or
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
};
