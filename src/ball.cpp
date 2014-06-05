#include "ball.hpp"
#include "utils.hpp"
#include "pong.hpp"
#include "paddle.hpp"

#include <iostream>

/**
 * @brief Ball::Ball The Ball implementation of the class Ball.
 * @param ballImage
 * @param ballRenderer
 * @param xVelocity
 * @param yVelocity
 * @param xCor
 * @param yCor
 * @param width
 * @param height
 */
Ball::Ball(SDL_Surface* ballSurface, SDL_Renderer** ballRenderer,
           double xVelocity, double yVelocity, float xCor, float yCor,
           int width, int height)
{
    if(ballSurface == NULL || ballRenderer == NULL)
        std::cout << "\nThe ball surface or the ball renderer passed, is null."
                  << std::endl;

    //Arguments initialization
    this->ballRect = new SDL_Rect();

    this->ballSurface   = ballSurface;

    setXVelocity(xVelocity);
    setYVelocity(yVelocity);

    this->ballRect->x   = xCor;
    this->ballRect->y   = yCor;
    this->ballRect->w   = width;
    this->ballRect->h   = height;

    this->ballTexture = SDL_CreateTextureFromSurface(*ballRenderer, ballSurface);

    if(this->ballTexture == NULL)
        std::cout << "LOG_ERR: failed to create ballTexture, error: " << SDL_GetError()
                  << std::endl;

    this->ballRenderer = *ballRenderer;

    if(this->ballTexture == NULL)
        std::cout << "LOG_ERR: failed to create ballRenderer, error: " << SDL_GetError()
                  << std::endl;

    SDL_FreeSurface(ballSurface);

    std::cout << "LOG: Ball created perfectly! :)" << std::endl;
}

Ball::~Ball()
{
    SDL_DestroyTexture(this->ballTexture);
    SDL_DestroyRenderer(this->ballRenderer);
    delete this->ballRect;
}

void Ball::show()
{
    SDL_RenderCopy(this->ballRenderer, this->ballTexture, NULL, this->ballRect);
}

void Ball::move(SDL_Rect* player1, SDL_Rect* player2)
{
    Pong pong;
    /* If the ball was moved then add the equivalent velocity of the ball to
     * the rectangle cordinates on the screen
     */
    this->ballRect->x += this->xVelocity;
    this->ballRect->y += this->yVelocity;

    //Detecting the collision on the Y axis.
    if(this->ballRect->y <= 0)
        this->yVelocity = -yVelocity;
    if(this->ballRect->y+ballRect->h > pong.getHeight())
        this->yVelocity = -yVelocity;
    //Detecting the collision with the paddles.
    if(collision(ballRect, player1)) {
        //almost fixed the freaking bug
        //4 pixel to added due to the speed of the ball in pixel/frame
        if(ballRect->x+3 < player1->x + player1->w)
            this->yVelocity = -yVelocity;
        else
            this->xVelocity = -xVelocity;
    }
    if(collision(ballRect, player2)) {
        //amost fixed the freaking bug
        if((ballRect->x + ballRect->w)-4 > player2->x)
            this->yVelocity = -yVelocity;
        else
            this->xVelocity = -xVelocity;
    }
}

/**
 * @brief Ball::collision A function to test the collision between to SDL_Rect
 * @param rect1 The first rect that we wanna to test the collision
 * @param rect2 The second rect that we wanna to test the collision
 * @return If a collision occurs or not
 */
bool Ball::collision(SDL_Rect* rect1, SDL_Rect* rect2)
{
    if(rect1->y >= rect2->y + rect2->h)
        return false;
    if(rect1->x >= rect2->x + rect2->w)
        return false;
    if(rect1->y + rect1->h <= rect2->y)
        return false;
    if(rect1->x + rect1->w <= rect2->x)
        return false;
    return true;
}


SDL_Rect* Ball::getBallRect()
{
    return this->ballRect;
}


float Ball::getXVelocity()
{
    return this->xVelocity;
}

float Ball::getYVelocity()
{
    return this->yVelocity;
}

void Ball::setXVelocity(double xVelocity)
{
    this->xVelocity = xVelocity;
}

void Ball::setYVelocity(double yVelocity)
{
    this->yVelocity = yVelocity;
}
