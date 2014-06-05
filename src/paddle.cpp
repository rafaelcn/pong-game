#include "paddle.hpp"
#include "pong.hpp"

#include <iostream>

/**
 * @brief Paddle::Paddle Constructor of the class that initializes the values
 * of the private variables with the given parameters for the class.
 * @param paddleSurface The surface that carries the image of the paddle.
 * @param paddleRenderer The renderer which will be used to render the paddle.
 * texture on the screen.
 * @param yVelocity The velocity in the Y axis of the paddle.
 * @param xCor The actual position in X axis of the paddle.
 * @param yCor The actual position in Y axis of the paddle.
 * @param width The width size of the paddle.
 * @param height The height size of the paddle.
 */
Paddle::Paddle(SDL_Surface* paddleSurface, SDL_Renderer** paddleRenderer,
               float yVelocity, float xCord, float yCord, int width, int height)
{
    if(paddleSurface == NULL || paddleRenderer == NULL)
        std::cout << "\nLOG_ERR: The paddle surface or paddle renderer passed,"
                  << "is null." << std::endl;

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
        std::cout << "LOG_ERR: failed to create paddleTexture, error: "
                  << SDL_GetError() << std::endl;

    this->paddleRenderer = *paddleRenderer;

    if(this->paddleRenderer == NULL)
        std::cout << "LOG_ERR: failed to create paddleRenderer, error: "
                  << SDL_GetError() << std::endl;

    SDL_FreeSurface(paddleSurface);

    if(this->paddleTexture != NULL)
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
 * @brief Paddle::getScore Function to get the actual score of the player.
 * @return
 */
int Paddle::getScore()
{
    return this->score;
}

/**
 * @brief Paddle::addScore Function to add 1 point to the player score.
 */
void Paddle::addScore()
{
    this->score++;
}
