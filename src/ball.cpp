#include "ball.hpp"
#include "game.hpp"
#include "window.hpp"
#include "debug.hpp"

#include <iostream>
#include <cmath>

Ball::Ball(SDL_Surface* ball_surface, const float coordinate_x,
           const float coordinate_y) : m_ball_speed(get_random_pos(-5, 5),
                                                    get_random_pos(-3, 3)),
                                       m_last_ball_speed(m_ball_speed())
{
    if(ball_surface == nullptr)
    {
        Debug::log_err("The ball surface is null. Check if res folder is along",
        "with the executable.");
    }
    else
    {
        m_ball_size[0] = 10;
        m_ball_size[1] = 10;

        m_pBSurface = ball_surface;

        m_BRect.x   = coordinate_x;
        m_BRect.y   = coordinate_y;
        m_BRect.w   = m_ball_size[0];
        m_BRect.h   = m_ball_size[1];

        m_pBTexture = SDL_CreateTextureFromSurface(Window::get_renderer(),
                                                   ball_surface);

        if(m_pBTexture == nullptr)
        {
            Debug::log_err("Failed to create ball texture!", SDL_GetError());
        }

        if(m_pBTexture == nullptr)
        {
            Debug::log_err("Failed to create ball renderer!", SDL_GetError());
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
}

void Ball::show()
{
    SDL_RenderCopy(Window::get_renderer(), m_pBTexture, nullptr, &m_BRect);
}

void Ball::move(SDL_Rect* player1, SDL_Rect* player2)
{
    m_BRect.x += velocity_x();
    m_BRect.y += velocity_y();

    //Detecting the collision in the Y axis.
    if(m_BRect.y <= 0)
    {
        velocity_y(-m_ball_speed.y());
        m_last_ball_speed = m_ball_speed;
    }
    if(m_BRect.y+m_BRect.h > Window::get_height())
    {
        velocity_y(-m_ball_speed.y());
        m_last_ball_speed = m_ball_speed;
    }

    //Detecting the collision with the players.
    if(collision(player1))
    {
        if (m_BRect.x + abs(velocity_x()) < player1->x + player1->w) {
            velocity_y(-m_ball_speed.y());
        }
        else {
            if (Paddle::get_hits() == 3) {
                add_speed();
                velocity_x(-m_ball_speed.x());
                Paddle::reset_hit_count();
            }
            else {
                velocity_x(-m_ball_speed.x());
            }
        }

        m_last_ball_speed = m_ball_speed;

        if(Game::audio->is_open()) {
            Game::audio->play_effect(Audio::EffectType::hit_paddle);
        }

        Debug::log("Hit count: ", Paddle::get_hits());
        Paddle::add_hit();
    }
    if(collision(player2))
    {
        if ((m_BRect.x + m_BRect.w)-velocity_x() > player2->x) {
            velocity_y(-m_ball_speed.y());
        }
        else {
            velocity_x(-m_ball_speed.x());
            if(Paddle::get_hits() == 3) {
                add_speed();
                Paddle::reset_hit_count();
            }
            else {

            }
        }

        m_last_ball_speed = m_ball_speed;

        if(Game::audio->is_open()) {
            Game::audio->play_effect(Audio::EffectType::hit_paddle);
        }

        Debug::log("Hit count: ", Paddle::get_hits());
        Paddle::add_hit();
    }
}

void Ball::add_speed()
{
    if (velocity_x() < 0.0f) {
        m_ball_speed += m_ball_speed() * m_random.get_real(0.1f, 0.15f);
        m_last_ball_speed = m_ball_speed;
    }
    else {
        m_ball_speed += m_ball_speed() * m_random.get_real(0.1f, 0.15f);
        m_last_ball_speed = m_ball_speed;
    }

    Debug::log("New speed is: x(", velocity_x(), ") y(", velocity_y(), ")");
}

bool Ball::collision(SDL_Rect* rectangle)
{
    if(m_BRect.y >= rectangle->y + rectangle->h)
    {
        return false;
    }
    if(m_BRect.x >= rectangle->x + rectangle->w)
    {
        return false;
    }
    if(m_BRect.y + m_BRect.h <= rectangle->y)
    {
        return false;
    }
    if(m_BRect.x + m_BRect.w <= rectangle->x)
    {
        return false;
    }
    return true;
}

SDL_Rect* Ball::get_rect()
{
    return &m_BRect;
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
    float position;

    do
    {
        position = m_random.get_real(a, b);
    }while((position >= 0.0f && position <= 3.0f) ||
           (position <= -0.0f && position >= -2.0f));

    return position;
}

void Ball::velocity_x(float velocity_x)
{
    m_ball_speed.x(velocity_x);
}

void Ball::velocity_y(float velocity_y)
{
    m_ball_speed.y(velocity_y);
}
