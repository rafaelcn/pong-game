/*
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

#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL2/SDL.h>

#include "window.hpp"

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
    SDL_Surface* m_pPSurface;
    //The paddle itself, it's the texture of the paddleImage.
    SDL_Texture* m_pPTexture;
    //SDL_Rect that will represent the size of the paddle on the screen.
    SDL_Rect m_PRect;

public:
    /**
     * @brief Constructor of the class that initializes the values
     * of the private variables with the given parameters for the class.
     * @param paddle_image The surface that carries the image of the paddle.
     * @param coordinate_x
     * @param coordinate_y
     */
    Paddle(SDL_Surface *paddle_image, const float coordinate_x,
           const float coordinate_y);
    ~Paddle();

    /**
     * @brief Returns the actual SDL_Rect* used to represent the
     * paddle.
     * @return The current SDL_Rect* used to represent the paddle
     */
    SDL_Rect* get_rect();

    /**
     * @brief This function just "blit"(SDL 1.2) the texture on the
     * renderer.
     */
    void show();
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
     * @brief get_hits Get the total number of times that the ball has hitted
     * the paddle.
     * @return An integer representing the number of times that the ball has
     * hitted the paddle.
     */
    static int get_hits();
    /**
     * @brief reset_hit_count Set the number of times that the ball has hitted
     * the paddle to zero.
     */
    static void reset_hit_count();
    /**
     * @brief reset_score Set the score of the paddle to zero.
     */
    void reset_score();

    /**
     * @brief The key_state holds the
     */
    const std::uint8_t* key_state;

};

#endif // PADDLE_HPP
