#include "paddle.hpp"
#include "pong.hpp"

#include <iostream>

/**
 * @brief Paddle::Paddle Constructor of the class that initializes the values
 * of the private variables with the given parameters for the class.
 * @param paddleSurface
 * @param paddleRenderer
 * @param yVelocity
 * @param xCord
 * @param yCord
 * @param width
 * @param height
 */
Paddle::Paddle(SDL_Surface* paddleSurface, SDL_Renderer** paddleRenderer,
               float yVelocity, float xCord, float yCord, int width, int height)
{
    if(paddleSurface == NULL || paddleRenderer == NULL)
        std::cout << "\nThe paddle surface or paddle renderer passed, is null."
                  << std::endl;

    //Arguments initialization
    this->paddleRect = new SDL_Rect();

    this->score = 0;

    this->paddleSurface         = paddleSurface;
    this->yVelocity             = yVelocity;
    this->paddleRect->x         = xCord;
    this->paddleRect->y         = yCord;
    this->paddleRect->w         = width;
    this->paddleRect->h         = height;

    this->paddleTexture = SDL_CreateTextureFromSurface(*paddleRenderer,
                                                 paddleSurface);

    if(this->paddleTexture == NULL)
        std::cout << "LOG_ERR: failed to create paddleTexture, error: " << SDL_GetError()
                  << std::endl;

    this->paddleRenderer = *paddleRenderer;

    if(this->paddleRenderer == NULL)
        std::cout << "LOG_ERR: failed to create paddleRenderer, error: " << SDL_GetError()
                  << std::endl;

    SDL_FreeSurface(paddleSurface);

    std::cout << "LOG: Paddle created perfectly! :)" << std::endl;
}

Paddle::~Paddle()
{
    SDL_DestroyTexture(this->paddleTexture);
    SDL_DestroyRenderer(this->paddleRenderer);
    delete this->paddleRect;
}

void Paddle::show()
{
    SDL_RenderCopy(this->paddleRenderer, this->paddleTexture, NULL,
                   this->paddleRect);
}

void Paddle::moveUp()
{
    /* The minus sign it's because the top left corner of the screen  is like
     * (0,0), so we have to subtract the value  of the  paddleRect->y  by the
     * yVelocity.
     * The if statement there is because due the bug of the paddle going out of
     * the screen, I'm limiting the up movement of the paddle by doing the
     * following statement.
     */
    if(this->paddleRect->y > 0)
        this->paddleRect->y -= this->yVelocity;
}

void Paddle::moveDown()
{
    Pong pong;
    /* Same thing here, but the bottom left corner of the screen is like (0, 1)
     * for (x, y) values, so we have to add (...).
     * The if statement is the same logic used on moveUp(); but here has a POG.
     */
    if(this->paddleRect->y+this->paddleRect->h < pong.getHeight())
        this->paddleRect->y += this->yVelocity;
}

/**
 * @brief Paddle::getRect Returns the actual SDL_Rect* used to represent the
 * paddle.
 * @return the current SDL_Rect* used to represent the paddle
 */
SDL_Rect* Paddle::getRect()
{
    return this->paddleRect;
}

/**
 * @brief Paddle::getScore
 * @return
 */
int Paddle::getScore()
{
    return this->score;
}

/**
 * @brief Paddle::addScore
 */
void Paddle::addScore()
{
    this->score++;
}
