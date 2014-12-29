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

#ifndef BALL_HPP
#define BALL_HPP

#include <SDL2/SDL.h>

#include "paddle.hpp"
#include "audio.hpp"

/*Forward class declaration because of the circular #include(The header guard
 * was not working in this case).
 */
class Game;

class Ball
{
    struct ball_characteristics {
        //Velocity of the ball on the screen.
        float velocity_x;
        float velocity_y;
        int width   = 10;
        int heigth  = 10;
    } ball_characteristics;

    /* The surface that will be used to be filled with the image of the ball
     * (ball.bmp).
     */
    SDL_Surface* m_pBSurface;
    //The texture of the ball(ball.bmp).
    SDL_Texture* m_pBTexture;
    //SDL_Rect that will represent the size of the ball on the screen.
    SDL_Rect* m_pBRect;

    bool collision(SDL_Rect* rectangle1, SDL_Rect* rectangle2);

public:
    Ball(SDL_Surface* ball_surface,
         float coordinate_x, float coordinate_y);
    ~Ball();

    void show();
    void move(SDL_Rect* player1, SDL_Rect* player2);
    void update_score(Paddle* player1, Paddle* player2);

    double velocity_x();
    double velocity_y();

    void velocity_x(double velocity_x);
    void velocity_y(double velocity_y);

    SDL_Rect* get_rect();
};

#endif // BALL_HPP
