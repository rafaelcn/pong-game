#include "ball.hpp"
#include "utils.hpp"
#include "pong.hpp"
#include "debug.hpp"
#include "sdl_audio.h"

#include <iostream>
#include <cmath>

/**
 * @brief Ball::Ball The Ball implementation of the class Ball.
 * @param ballSurface The surface that carries the image of the ball.
 * @param ballRenderer The renderer which will be used to render the ball
 * texture on the screen.
 * @param xCor The actual position in X axis of the ball.
 * @param yCor The actual position in Y axis of the ball.
 * @param width The width size of the ball.
 * @param height The height size of the ball.
 */
Ball::Ball(SDL_Surface* ballSurface, SDL_Renderer** ballRenderer, float xCor,
           float yCor, int width, int height)
{
    if(ballSurface == NULL || ballRenderer == NULL)
        logerr("The ball surface or the ball renderer passed is null.");
    else
    {
        //Arguments initialization
        this->ballRect = new SDL_Rect();

        this->ballSurface   = ballSurface;

        setXVelocity(2.0);
        setYVelocity(0.0);

        this->ballRect->x   = xCor;
        this->ballRect->y   = yCor;
        this->ballRect->w   = width;
        this->ballRect->h   = height;

        this->ballTexture = SDL_CreateTextureFromSurface(*ballRenderer,
                                                         ballSurface);

        if(this->ballTexture == NULL)
        {
            logerr("Failed to create ballTexture!");
            logerr(SDL_GetError());
        }

        this->ballRenderer = *ballRenderer;

        if(this->ballTexture == NULL)
        {
            logerr("Failed to create ballRenderer");
            logerr(SDL_GetError());
        }

        SDL_FreeSurface(ballSurface);

        if(this->ballTexture != NULL)
            log("Ball created perfectly! :)");
    }
}

Ball::~Ball()
{
    SDL_DestroyTexture(this->ballTexture);
    SDL_DestroyRenderer(this->ballRenderer);
    delete this->ballRect;
}

/**
 * @brief Ball::show This function just "blit"(SDL 1.2) the texture on the
 * renderer.
 */
void Ball::show()
{
    SDL_RenderCopy(this->ballRenderer, this->ballTexture, NULL, this->ballRect);
}

void Ball::move(SDL_Rect* player1, SDL_Rect* player2, Pong* pongObject,
                AudioWrapper* audio)
{
    this->ballRect->x += this->getXVelocity();
    this->ballRect->y += this->getYVelocity();

    //Detecting the collision on the Y axis.
    if(this->ballRect->y <= 0)
        this->yVelocity = -yVelocity;
    if(this->ballRect->y+ballRect->h > pongObject->getHeight())
        this->yVelocity = -yVelocity;
    //Detecting the collision with the paddles.
    if(collision(ballRect, player1)) {
        /* Still need to fix the collision detection, it looks like the
         * collision with the player 1 doesn't work at  21.5 of  speed.
         * The bug is not only in the player1, it does so in the player 2
         * as well.
         */
        if(ballRect->x+abs(this->getXVelocity()) < player1->x + player1->w)
            this->yVelocity = -yVelocity;
        else
            this->xVelocity = -xVelocity;
        audio->playEffect();

        log(pongObject->getHits());
        pongObject->addHit();
    }
    if(collision(ballRect, player2)) {
        if((ballRect->x + ballRect->w)-xVelocity > player2->x)
            this->yVelocity = -yVelocity;
        else
            this->xVelocity = -xVelocity;
        audio->playEffect();

        log(pongObject->getHits());
        pongObject->addHit();
    }

    //The fun begins when the speed gets higher :3
    if(pongObject->getHits() == 4) {
        std::cout << "Actual speed: " << getXVelocity() << std::endl;
        if(getXVelocity() < 0.0)
            setXVelocity(getXVelocity() + (-0.5));
        else
            setXVelocity(getXVelocity() + 0.5);

        pongObject->resetHitCount();
        std::cout << "New speed is: x(" << this->getXVelocity() << ") y("
                  << this->getYVelocity() << ")" << std::endl;
    }
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
        return false;
    if(rect1->x >= rect2->x + rect2->w)
        return false;
    if(rect1->y + rect1->h <= rect2->y)
        return false;
    if(rect1->x + rect1->w <= rect2->x)
        return false;
    return true;
}

/**
  * @brief Ball::getBallRect() Function to return the SDL_Rect* of the ball.
  * @return the
  */
SDL_Rect* Ball::getBallRect()
{
    return this->ballRect;
}

double Ball::getXVelocity()
{
    return this->xVelocity;
}

double Ball::getYVelocity()
{
    return this->yVelocity;
}

/**
 * @brief Ball::setXVelocity Function to set the velocity on the X axis of the
 * ball.
 * @param xVelocity The velocity on X axis.
 */
void Ball::setXVelocity(double xVelocity)
{
    this->xVelocity = xVelocity;
}

/**
 * @brief Ball::setYVelocity Function to set the velocity on the Y axis of the
 * ball.
 * @param yVelocity The velocity on Y axis.
 */
void Ball::setYVelocity(double yVelocity)
{
    this->yVelocity = yVelocity;
}
