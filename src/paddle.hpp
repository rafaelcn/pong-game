/*
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

#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

class Paddle
{
    //Velocity of the paddle on the screen.
    int yVelocity;
    //Score of the paddle
    int score;
    //The image of the paddle that will be loaded on a surface.
    SDL_Surface* paddleSurface;
    //The paddle itself, it's the texture of the paddleImage.
    SDL_Texture* paddleTexture;
    //The renderer that the ballTexture will use to draw on the screen.
    SDL_Renderer* paddleRenderer;
    //SDL_Rect that will represent the size of the paddle on the screen.
    SDL_Rect* paddleRect;
public:
    Paddle(SDL_Surface* paddleImage, SDL_Renderer** paddleRenderer,
           float yVelocity, float xCord, float yCord, int width, int height);
    ~Paddle();

    //getting the rect of the paddle.
    SDL_Rect* getRect();

    void show();
    void moveUp();
    void moveDown();

    //Getter and an score "adder".
    int getScore();
    void addScore();
};

#endif
