#include "paddle.hpp"
#include "window.hpp"
#include "debug.hpp"

#include <iostream>

int Paddle::m_hits;

/**
 * @brief Paddle::Paddle Constructor of the class that initializes the values
 * of the private variables with the given parameters for the class.
 * @param paddle_image The surface that carries the image of the paddle.
 */
Paddle::Paddle(SDL_Surface* paddle_image, float coordinate_x,
               float coordinate_y)
{
    if(paddle_image == nullptr) {
        Debug::logerr("The paddle surface is nullptr.");
    }
    else {
         m_pPRect = new SDL_Rect();

         m_score = 0;

         m_pPSurface         = paddle_image;
         m_pPRect->x         = coordinate_x;
         m_pPRect->y         = coordinate_y;
         m_pPRect->w         = paddle_characteristics.width;
         m_pPRect->h         = paddle_characteristics.height;

         m_pPTexture = SDL_CreateTextureFromSurface(Window::get_renderer(),
                                                    paddle_image);

        if( m_pPTexture == nullptr) {
            Debug::logerr("Failed to create paddleTexture!", SDL_GetError());
        }

        SDL_FreeSurface(paddle_image);

        if( m_pPTexture != nullptr) {
            Debug::log("Paddle created perfectly.");
        }
    }
}

Paddle::~Paddle()
{
    if(m_pPTexture != nullptr) {
        SDL_DestroyTexture( m_pPTexture);
    }
    delete  m_pPRect;
}

/**
 * @brief Paddle::show This function just "blit"(SDL 1.2) the texture on the
 * renderer.
 */
void Paddle::show()
{
    SDL_RenderCopy(Window::get_renderer(), m_pPTexture, nullptr, m_pPRect);
}

void Paddle::move_up()
{
    /* The minus sign it's because the top left corner of the screen  is like
     * (0,0), so we have to subtract the value  of the  paddleRect->y  by the
     * yVelocity.
     * The if statement there is because due the bug of the paddle going out of
     * the screen, I'm limiting the up movement of the paddle by doing the
     * following statement.
     */
    if( m_pPRect->y > 0) {
         m_pPRect->y -=  paddle_characteristics.velocity_y;
    }
}

void Paddle::move_down()
{
    /* Same thing here, but the bottom left corner of the screen is like (0, 1)
     * for (x, y) values, so we have to add (...).
     * The if statement is the same Debug::logic used on moveUp(); but here has a POG.
     */
    if(m_pPRect->y + m_pPRect->h < Window::get_height()) {
        m_pPRect->y +=  paddle_characteristics.velocity_y;
    }
}

/**
 * @brief Paddle::getRect Returns the actual SDL_Rect* used to represent the
 * paddle.
 * @return the current SDL_Rect* used to represent the paddle
 */
SDL_Rect* Paddle::get_rect()
{
    return m_pPRect;
}

/**
 * @brief Paddle::getYVelocity a getter for the paddle velocity.
 * @return the current velocity on the Y axis.
 */
double Paddle::velocity_y()
{
    return paddle_characteristics.velocity_y;
}

/**
 * @brief Paddle::velocity_y a setter for the paddle velocity.
 * @param yVelocity the velocity of the paddle on the Y axis.
 */
void Paddle::velocity_y(double velocity_y)
{
     paddle_characteristics.velocity_y = velocity_y;
}

/**
 * @brief Paddle::score get the actual score of the player.
 * @return the actual score of the player.
 */
int Paddle::score()
{
    return m_score;
}

/**
 * @brief Paddle::addScore Function to add 1 point to the player score.
 */
void Paddle::add_score()
{
    m_score++;
}

/**
 * @brief Paddle::get_hits
 * @return
 */
int Paddle::get_hits()
{
    return m_hits;
}

/**
 * @brief Paddle::add_hit
 */
void Paddle::add_hit()
{
    m_hits += 1;
}

/**
 * @brief Paddle::reset_hit_count
 */
void Paddle::reset_hit_count()
{
    m_hits = 0;
}
