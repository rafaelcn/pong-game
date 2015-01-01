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

#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <cstdint>

#include <SDL2/SDL.h>

#include "window.hpp"

class Paddle {
private:
    /**
     * @brief The paddle_characteristcs struct is the container of almost all
     * characteristics like it velocity, width and height.
     */
    struct paddle_characteristics {
        float velocity_y    = 6.0f;
        int width           = 10;
        int height          = 50;
    } paddle_characteristics;

    // Hit counter used to speed up the ball.
    static int m_hits;
    //Score of the paddle (player)
    int m_score;
    //The image of the paddle that will be loaded on a surface.
    SDL_Surface* m_pPSurface;
    //The paddle itself, it's the texture of the paddleImage.
    SDL_Texture* m_pPTexture;
    //SDL_Rect that will represent the size of the paddle on the screen.
    SDL_Rect* m_pPRect;
public:
    Paddle(SDL_Surface *paddle_image, const float coordinate_x,
           const float coordinate_y);
    ~Paddle();

    //getting the rect of the paddle.
    SDL_Rect* get_rect();

    void show();
    void move_up();
    void move_down();

    /**
     * @brief velocity_y
     * @return
     */
    double velocity_y();
    /**
     * @brief velocity_y
     * @param velocity_y_
     */
    void velocity_y(const double velocity_y);

    /**
     * @brief score
     * @return
     */
    int score();
    /**
     * @brief add_score
     */
    void add_score();
    /**
     * @brief add_hit
     */
    static void add_hit();
    /**
     * @brief get_hits
     * @return
     */
    static int get_hits();
    /**
     * @brief reset_hit_count
     */
    static void reset_hit_count();
    /**
     * @brief reset_score
     */
    void reset_score();

    /**
     * @brief The paddle_moviment struct
     */
    struct paddle_moviment {
        const u_int8_t* key_state;
        bool player_keys[2] = { false, false };
    } paddle_moviment;

};

#endif // PADDLE_HPP
