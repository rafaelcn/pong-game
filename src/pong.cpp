#include "pong.hpp"
#include "ball.hpp"
#include "paddle.hpp"

#include <iostream>
#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


/**
 * @brief Pong::Pong
 */
Pong::Pong()
{
    this->WIDTH   = 800;
    this->HEIGHT  = 600;

    this->hits = 0;

    this->FPS = 60;

    this->fontRect = NULL;
    this->fontSurface = NULL;
    this->fontTexture = NULL;
    this->fontRenderer = NULL;
}

Pong::Pong(Paddle *player1, Paddle *player2)
{
    this->WIDTH   = 800;
    this->HEIGHT  = 600;

    this->hits = 0;

    this->FPS = 60;

    this->fontRect = NULL;
    this->fontSurface = NULL;
    this->fontTexture = NULL;
    this->fontRenderer = NULL;
}

/**
 * @brief Pong::Pong This constructor is intend to render the score to my game
 * view.
 * @param player a pointer to a Paddle which is the player to get the score.
 * @param font the TTF_Font that will be used.
 * @param fontRenderer the renderer which the font will be rendered
 * @param fontColor the SDL_Color of the font as the name says.
 * @param xCord where in X axis the font will be rendered.
 * @param yCord where in Y axis the font will be rendered.
 */
Pong::Pong(Paddle* player, TTF_Font** font, SDL_Renderer** fontRenderer,
           SDL_Color &fontColor, int xCord, int yCord)
{
    this->fontRect      = new SDL_Rect();
    this->fontRenderer  = *fontRenderer;
    this->player        = player;
    this->font          = *font;
    this->fontColor     = fontColor;

    if(this->fontRenderer == NULL)
        std::cout << "LOG_ERR: font renderer is NULL! " << std::endl;

    this->fontRect->h = 100;
    this->fontRect->w = 50;
    this->fontRect->x = xCord;
    this->fontRect->y = yCord;
}

Pong::~Pong()
{
    SDL_DestroyTexture(this->fontTexture);
    SDL_DestroyRenderer(this->fontRenderer);
    delete this->fontRect;

}

/**
 * @brief Pong::renderScore This function renders the score on the screen.
 */
void Pong::renderScore()
{
    //to_string available only in c++11. Flag: -std=c++11
   std::string score = std::to_string(this->player->getScore());

   this->fontSurface = TTF_RenderText_Solid(this->font, score.c_str(),
                                            this->fontColor);

   if(this->fontSurface == NULL)
       std::cout << "LOG_ERR: font surface is NULL, error: " << TTF_GetError()
                 << std::endl;

   this->fontTexture = SDL_CreateTextureFromSurface(this->fontRenderer,
                                                    this->fontSurface);

   SDL_FreeSurface(this->fontSurface);

   if(this->fontTexture == NULL)
       std::cout << "LOG_ERR: font texture is NULL, error: " << SDL_GetError()
                 << std::endl;

   SDL_RenderCopy(this->fontRenderer, this->fontTexture, NULL, this->fontRect);

   //delete this line and your computer goes wild! (REALLY, DON'T DO THAT).
   SDL_DestroyTexture(this->fontTexture);
   /*
    *                           ~EXPLANATION~
    * Destroy the texture and then create other, because if  when you call this
    * function it recreate the texture, and it allocate more RAM, over and over
    * again,  resulting  in swapping all your memory, and after  that I stopped
    * the application, so I can't tell what happens next. :p
    */
}

/**
 * @brief Pong::getWidth
 * @return
 */
int Pong::getWidth()
{
    return this->WIDTH;
}

/**
 * @brief Pong::getHeight
 * @return
 */
int Pong::getHeight()
{
    return this->HEIGHT;
}

/**
 * @brief Pong::getHits
 * @return
 */
int Pong::getHits()
{
    return this->hits;
}

unsigned int Pong::getFPS() const
{
    return this->FPS;
}

void Pong::addHit()
{
    this->hits++;
}


/**
 * @brief Pong::updateGameState
 * @param player1
 * @param player2
 * @param ballObject
 */
void Pong::updateGameState(Paddle* player1, Paddle* player2, Ball* ballObject)
{
    SDL_Rect* ballRect = ballObject->getBallRect();

    if(ballRect->x+ballRect->w > Pong::getWidth())
    {
        player1->addScore();
        resetGameState(player1, player2, ballObject);
        std::cout << "Player 1 score: " << player1->getScore() << std::endl;
    }
    if(ballRect->x+ballRect->w < 0)
    {
        player2->addScore();
        resetGameState(player1, player2, ballObject);
        std::cout << "Player 2 score: " << player2->getScore() << std::endl;
    }
}

/**
 * @brief Pong::resetGameState The function resets the game state, setting back
 * the ball amd the paddles position.
 * @param player1 A pointer to the player1 object(paddle).
 * @param player2 A pointer to the player2 object(paddle).
 * @param ballObject A pointer to the ball.
 */
void Pong::resetGameState(Paddle* player1, Paddle* player2, Ball* ballObject)
{
    SDL_Rect* ballRect = ballObject->getBallRect();

    SDL_Rect* player1Rect = player1->getRect();
    SDL_Rect* player2Rect = player2->getRect();

    //reseting hits on the paddle
    this->hits = 0;

    //Reseting ball to default position and velocity
    ballObject->setXVelocity(2.0);
    ballObject->setYVelocity(2.0);
    ballRect->x = Pong::getWidth()/2-(ballRect->w);
    ballRect->y = Pong::getHeight()/2-(ballRect->h);

    //Reseting the paddles to default position
    player1Rect->y = Pong::getHeight()/2-(player1Rect->h/2);
    player2Rect->y = Pong::getHeight()/2-(player2Rect->h/2);

}
