#include "ball.hpp"
#include "utils.hpp"
#include "game.hpp"
#include "window.hpp"
#include "debug.hpp"

#include <iostream>
#include <cmath>

/**
 * @brief Ball::Ball The Ball implementation of the class Ball.
 * @param ball_surface The surface that carries the image of the ball.
 * @param window_renderer The renderer which will be used to render the ball
 * texture on the screen.
 * @param coordinate_x The actual position in X axis of the ball.
 * @param coordinate_y The actual position in Y axis of the ball.
 */
Ball::Ball(SDL_Surface* ball_surface, float coordinate_x, float coordinate_y)
{
    if(ball_surface == nullptr) {
        Debug::logerr("The ball surface is null.");
    }
    else {
        m_pBRect = new SDL_Rect();
        m_pBSurface     = ball_surface;

        velocity_x(2.0);
        velocity_y(1.0);

        m_pBRect->x   = coordinate_x;
        m_pBRect->y   = coordinate_y;
        m_pBRect->w   = ball_characteristics.width;
        m_pBRect->h   = ball_characteristics.heigth;

        m_pBTexture = SDL_CreateTextureFromSurface(Window::get_renderer(),
                                                   ball_surface);

        if(m_pBTexture == nullptr) {
            Debug::logerr("Failed to create ball texture!", SDL_GetError());
        }

        if(m_pBTexture == nullptr) {
            Debug::logerr("Failed to create ball renderer", SDL_GetError());
        }

        SDL_FreeSurface(ball_surface);

        if(m_pBTexture != nullptr) {
            Debug::log("Ball created perfectly!");
        }
    }
}

Ball::~Ball()
{
    if(m_pBTexture != nullptr) {
        SDL_DestroyTexture(m_pBTexture);
    }
    delete m_pBRect;
}

/**
 * @brief Ball::show This function just "blit"(SDL 1.2) the texture on the
 * renderer.
 */
void Ball::show()
{
    SDL_RenderCopy(Window::get_renderer(), m_pBTexture, nullptr, m_pBRect);
}

void Ball::move(SDL_Rect* player1, SDL_Rect* player2)
{
    m_pBRect->x += velocity_x();
    m_pBRect->y += velocity_y();

    //Detecting the collision on the Y axis.
    if(m_pBRect->y <= 0) {
        velocity_y(-ball_characteristics.velocity_y);
    }
    if(m_pBRect->y+m_pBRect->h > Window::get_height()) {
        velocity_y(-ball_characteristics.velocity_y);
    }
    //Detecting the collision with the players.
    if(collision(m_pBRect, player1))
    {
        /* Still need to fix the collision detection, it looks like the
         * collision with the player 1 doesn't work at  21.5 of  speed.
         * The bug is not only in the player1, it does so in the player 2.
         */
        if(m_pBRect->x+abs(velocity_x()) < player1->x + player1->w) {
            velocity_y(-ball_characteristics.velocity_y);
        }
        else {
            velocity_x(-ball_characteristics.velocity_x);
        }

        //if(audio->is_open()) {
        //    audio->play_effect();
        //}

        //Debug::log("Hit count: " + game->get_hits());
        //game->add_hit();
    }
    if(collision(m_pBRect, player2)) {
        if((m_pBRect->x + m_pBRect->w)-velocity_x() > player2->x) {
            velocity_y(-ball_characteristics.velocity_y);
        }
        else  {
            velocity_x(-ball_characteristics.velocity_x);
        }

        //if(audio->is_open()) {
        //    audio->play_effect();
        //}

        //Debug::log("Hit count: " + game->get_hits());
        //Paddle::add_hit();
    }

    //The fun begins when the speed gets higher :3
//    if(Paddle::get_hits() == 3)
//    {
//        Debug::log("Actual speed: ", velocity_x());

//        if(velocity_x() < 0.0) {
//            velocity_x(velocity_x() + (-0.5));
//        }
//        else {
//            velocity_x(velocity_x() + 0.5);
//        }

//        Paddle::reset_hit_count();
//        Debug::log("New speed is: x(", velocity_x(), ") y(", velocity_y(), ")");
//    }
}

/**
 * @brief Ball::collision A function to test the collision between two SDL_Rects.
 * @param rect1 The first rect that we wanna to test the collision.
 * @param rect2 The second rect that we wanna to test the collision.
 * @return If a collision occurs or not.
 */
bool Ball::collision(SDL_Rect* rect1, SDL_Rect* rect2)
{
    if(rect1->y >= rect2->y + rect2->h) {
        return false;
    }
    if(rect1->x >= rect2->x + rect2->w) {
        return false;
    }
    if(rect1->y + rect1->h <= rect2->y) {
        return false;
    }
    if(rect1->x + rect1->w <= rect2->x) {
        return false;
    }
    return true;
}

/**
  * @brief Ball::get_rect() Function to return the SDL_Rect* of the ball.
  * @return A pointer to the ballRect.
  */
SDL_Rect* Ball::get_rect()
{
    return m_pBRect;
}

/**
 * @brief Ball::velocity_x A function to get the velocity of the ball on the X
 * axis.
 * @return the velocity of the ball on the X axis.
 */
double Ball::velocity_x()
{
    return ball_characteristics.velocity_x;
}

/**
 * @brief Ball::velocity_y A function to get the velocity of the ball on the Y
 * axis.
 * @return the velocity of the ball on the Y axis.
 */
double Ball::velocity_y()
{
    return ball_characteristics.velocity_y;
}

/**
 * @brief Ball::velocity_x Function to set the velocity on the X axis of the
 * ball.
 * @param x_velocity The velocity on X axis.
 */
void Ball::velocity_x(double velocity_x)
{
    ball_characteristics.velocity_x = velocity_x;
}

/**
 * @brief Ball::velocity_y Function to set the velocity on the Y axis of the
 * ball.
 * @param velocity_y The velocity on Y axis.
 */
void Ball::velocity_y(double velocity_y)
{
    ball_characteristics.velocity_y = velocity_y;
}
