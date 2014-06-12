/* This class is just a prototype, not ready yet.
 *
 * Game: Pong Game.
 * Author: Rafael Campos Nunes.
 * License: Apache v2.
 *
 * Fell free to contact me on
 * Email: rafaelnunes737@hotmail.com
 * Github: https://github.com/rafaelcn
 *
 * Also you can contact me on IRC(freenode.net server) my nickname is: ranu.
 */

#ifndef PONG_H
#define PONG_H

#include <SDL2/SDL_ttf.h>

#include "ball.hpp"
#include "paddle.hpp"


class Pong
{
    //The size of the window(in windowed mode).
    int WIDTH, HEIGHT;
    //The hit counter by the paddles.
    int hits;
    //The desired FPS for the game.
    unsigned  int FPS;
    //If the game is paused or no.
    bool pause;
    //The player.
    Paddle* player;
    //The SDL_Rect that represents where and in which size the font will be
    //rendered.
    SDL_Rect* fontRect;
    //The renderer for where it will be rendered.
    SDL_Renderer* fontRenderer;
    //A surface that will be loading the font via TTF_RenderText_Solid(...);
    SDL_Surface* fontSurface;
    //The texture of the font.
    SDL_Texture* fontTexture;
    //The color of the font.
    SDL_Color fontColor;
    //The font itself.
    TTF_Font* font;

public:
    Pong();
    Pong(Paddle* player1, Paddle* player2);
    Pong(Paddle* player, TTF_Font** font, SDL_Renderer** fontRenderer,
         SDL_Color& fontColor, int xCord, int yCord);
    ~Pong();

    int getWidth();
    int getHeight();
    int getHits();
    unsigned int getFPS() const;

    void addHit();
    void resetHitCount();

    void pauseGame(Ball* ball, Paddle* player1, Paddle* player2);

    void renderScore();
    void updateGameState(Paddle* player1, Paddle* player2, Ball* ball);
    void resetGameState(Paddle* player1, Paddle* player2, Ball* ball);
};

#endif
