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

#ifndef BALL_HPP
#define BALL_HPP

#include <memory>
#include <array>

#include <SDL2/SDL.h>

#include "paddle.hpp"
#include "audio.hpp"
#include "vector2d.hpp"
#include "random.hpp"

class Ball {
private:
    /* An array describing the size of the ball, index 0 is width and the 1 is
     * the height.
     */
    std::array<int, 2> m_ball_size;

    Random m_random;
    // The ball speed represented by a Vector2D.
    Vector2D m_ball_speed;

    /* The surface that will be used to be filled with the image of the ball
     * (ball.bmp).
     */
    SDL_Surface* m_pBSurface;
    //The texture of the ball(ball.bmp).
    SDL_Texture* m_pBTexture;
    //SDL_Rect that will represent the size of the ball on the screen.
    SDL_Rect m_BRect;

private:
    void add_speed();
    /**
     * @brief Function to test the collision between the
     * rectangle of the ball and the rectangle of the players.
     * @param rectangle The rectangle we wanna to test the collision.
     * @return If a collision occurs or not.
     */
    bool collision(SDL_Rect *rectangle);

public:
    /**
     * @brief Is the variable used when pause game is toggled, it stores
     * the last speed with the ball.
     */
    Vector2D m_last_ball_speed;

public:
    /**
     * @brief The Ball implementation of the class Ball.
     * @param ball_surface The surface that carries the image of the ball.
     * @param coordinate_x The actual position in X axis of the ball.
     * @param coordinate_y The actual position in Y axis of the ball.
     */
    Ball(SDL_Surface* ball_surface, const float coordinate_x,
         const float coordinate_y);
    ~Ball();

    /**
     * @brief Called to show the ball in the screen.
     */
    void show();
    /**
     * @brief
     */
    void move(SDL_Rect* player1, SDL_Rect* player2);

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
     * @brief get_random_pos function to return a float between @param a and
     * @param b to be used as the start position of the ball.
     * @param a the range of the random generator.
     * @param b the range of the random generator.
     * @return a random integer.
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

#endif // BALL_HPP
