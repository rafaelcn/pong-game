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
Ball::Ball(SDL_Surface* ball_surface, const float coordinate_x,
           const float coordinate_y) : ball_speed(3.0f, 1.0f),
                                       last_ball_speed(ball_speed())
{
    if(ball_surface == nullptr)
    {
        Debug::logerr("The ball surface is null.");
    }
    else
    {
        m_pBRect        = new SDL_Rect();
        m_pBSurface     = ball_surface;

        m_pBRect->x   = coordinate_x;
        m_pBRect->y   = coordinate_y;
        m_pBRect->w   = ball_size.width;
        m_pBRect->h   = ball_size.heigth;

        m_pBTexture = SDL_CreateTextureFromSurface(Window::get_renderer(),
                                                   ball_surface);

        if(m_pBTexture == nullptr)
        {
            Debug::logerr("Failed to create ball texture!", SDL_GetError());
        }

        if(m_pBTexture == nullptr)
        {
            Debug::logerr("Failed to create ball renderer", SDL_GetError());
        }

        SDL_FreeSurface(ball_surface);

        if(m_pBTexture != nullptr)
        {
            Debug::log("Ball created perfectly!");
        }
    }
}

Ball::~Ball()
{
    if(m_pBTexture != nullptr)
    {
        SDL_DestroyTexture(m_pBTexture);
    }
    delete m_pBRect;
}

/**
 * @brief Ball::show This function just "blit" (SDL 1.2) the texture on the
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

    //Detecting the collision in the Y axis.
    if(m_pBRect->y <= 0)
    {
        velocity_y(-ball_speed.y());
    }
    if(m_pBRect->y+m_pBRect->h > Window::get_height())
    {
        velocity_y(-ball_speed.y());
    }

    //Detecting the collision with the players.
    if(collision(m_pBRect, player1))
    {
        if(m_pBRect->x+abs(velocity_x()) < player1->x + player1->w) {
            velocity_y(-ball_speed.y());
        }
        else {
            if(Paddle::get_hits() == 3)
            {
                add_speed();
            }
            velocity_x(-ball_speed.x());

        }

        last_ball_speed = ball_speed;

        //if(audio->is_open()) {
        //    audio->play_effect();
        //}

        Debug::log("Hit count: ", Paddle::get_hits());
        Paddle::add_hit();
    }
    if(collision(m_pBRect, player2))
    {
        if((m_pBRect->x + m_pBRect->w)-velocity_x() > player2->x)
        {
            velocity_y(-ball_speed.y());
        }
        else
        {
            if(Paddle::get_hits() == 3)
            {
                add_speed();
            }
            velocity_x(-ball_speed.x());
        }

        last_ball_speed = ball_speed;

        //if(audio->is_open()) {
        //    audio->play_effect();
        //}

        Debug::log("Hit count: ", Paddle::get_hits());
        Paddle::add_hit();
    }
}

void Ball::add_speed()
{
    // TODO: play some fancy effect when speeding up. And take a random number
    // to mutiply with the speed.
    if(velocity_x() < 0.0f)
    {
        ball_speed += ball_speed() * random_gen.get_real(0.1f, 0.3f);
        last_ball_speed = ball_speed();
    }
    else
    {
        ball_speed += ball_speed() * random_gen.get_real(0.1f, 0.2f);
        last_ball_speed = ball_speed();
    }

    Paddle::reset_hit_count();
    Debug::log("New speed is: x(", velocity_x(), ") y(", velocity_y(), ")");

}

/**
 * @brief Ball::collision A function to test the collision between two SDL_Rects.
 * @param rect1 The first rect that we wanna to test the collision.
 * @param rect2 The second rect that we wanna to test the collision.
 * @return If a collision occurs or not.
 */
bool Ball::collision(SDL_Rect* rect1, SDL_Rect* rect2)
{
    if(rect1->y >= rect2->y + rect2->h)
    {
        return false;
    }
    if(rect1->x >= rect2->x + rect2->w)
    {
        return false;
    }
    if(rect1->y + rect1->h <= rect2->y)
    {
        return false;
    }
    if(rect1->x + rect1->w <= rect2->x)
    {
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
float Ball::velocity_x()
{
    return ball_speed.x();
}

/**
 * @brief Ball::velocity_y A function to get the velocity of the ball on the Y
 * axis.
 * @return the velocity of the ball on the Y axis.
 */
float Ball::velocity_y()
{
    return ball_speed.y();
}

/**
 * @brief Ball::velocity_x Function to set the velocity on the X axis of the
 * ball.
 * @param x_velocity The velocity on X axis.
 */
void Ball::velocity_x(float velocity_x)
{
    ball_speed.x(velocity_x);
}

/**
 * @brief Ball::velocity_y Function to set the velocity on the Y axis of the
 * ball.
 * @param velocity_y The velocity on Y axis.
 */
void Ball::velocity_y(float velocity_y)
{
    ball_speed.y(velocity_y);
}
