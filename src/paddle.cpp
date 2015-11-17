#include "paddle.hpp"
#include "window.hpp"
#include "debug.hpp"

#include <iostream>

int Paddle::m_hits;

Paddle::Paddle(SDL_Surface* paddle_image, const float coordinate_x,
               const float coordinate_y)
{
    if(paddle_image == nullptr)
    {
        Debug::log_err("The paddle surface is null. Check if res folder is  \
         along with the executable.");
    }
    else
    {
        m_score = 0;

        m_pPSurface       = paddle_image;
        m_PRect.x         = coordinate_x;
        m_PRect.y         = coordinate_y;
        m_PRect.w         = paddle_characteristics.width;
        m_PRect.h         = paddle_characteristics.height;

        m_pPTexture = SDL_CreateTextureFromSurface(Window::get_renderer(),
                                                   paddle_image);

        if( m_pPTexture == nullptr)
        {
            Debug::log_err("Failed to create paddle texture!", SDL_GetError());
        }

        SDL_FreeSurface(paddle_image);

        if( m_pPTexture != nullptr)
        {
            Debug::log("Paddle created perfectly.");
        }
    }
}

Paddle::~Paddle()
{
    if(m_pPTexture != nullptr)
    {
        SDL_DestroyTexture(m_pPTexture);
    }
}

void Paddle::show()
{
    SDL_RenderCopy(Window::get_renderer(), m_pPTexture, nullptr, &m_PRect);
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
    if( m_PRect.y > 0)
    {
         m_PRect.y -=  paddle_characteristics.velocity_y;
    }
}

void Paddle::move_down()
{
    /* Same thing here, but the bottom left corner of the screen is like (0, 1)
     * for (x, y) values, so we have to add (...).
     * The if statement is the same Debug::logic used on moveUp(); but here has a POG.
     */
    if(m_PRect.y + m_PRect.h < Window::get_height())
    {
        m_PRect.y +=  paddle_characteristics.velocity_y;
    }
}

SDL_Rect* Paddle::get_rect()
{
    return &m_PRect;
}

double Paddle::velocity_y()
{
    return paddle_characteristics.velocity_y;
}

void Paddle::velocity_y(const double velocity_y)
{
     paddle_characteristics.velocity_y = velocity_y;
}

int Paddle::score()
{
    return m_score;
}

/**
 * @brief Paddle::reset_score
 */
void Paddle::reset_score()
{
    m_score = 0;
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
