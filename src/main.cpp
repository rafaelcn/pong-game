/**
  * This project was made with the intuit of learn the general and basic stuff
  * of the SDL2.  This  file  should be clean  and  small (it is NOT clean and
  * small), so  I'll  have  to separate  in  various  modules(classes, structs,
  * any kind of wrapper).
  *
  * Game: Pong Game.
  * Author: Rafael Campos Nunes.
  * License: Apache v2.
  *
  * Fell free to contact me on
  * Email: <rafaelnunes737@hotmail.com>
  * Github: <https://github.com/rafaelcn>
  *
  * Also you can contact me on IRC(freenode.net server) my nickname is: ranu.
  */


#include <iostream>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "sdl_audio.h"
#include "pong.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "utils.hpp"
#include "debug.hpp"

bool initSDL(SDL_Window** window, SDL_Renderer** windowRenderer,
             const int width,
             const int height);

bool initFont(TTF_Font** font, SDL_Color* fontColor);

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* windowRenderer = NULL;

    TTF_Font* font;
    SDL_Color fontColor;

    Mix_Chunk* effect;
    Mix_Music* music;

    int32_t ticksCount;

    Pong pong;

    if(!initSDL(&window, &windowRenderer, pong.getWidth(), pong.getHeight()))
    {
        return 1;
    }
    else if(!initFont(&font, &fontColor))
    {
        return 1;
    }
    else
    {
        //array of the keys used by the players
        bool playerKeys[4] = {false, false, false, false};
        //The exit condition for the main loop
        bool exit = false;

        SDL_Event event;

        #ifdef __WINDOWS__
            /* Windows only works with absolute paths! At least here only works
             * with absolute paths, or it is just me.
             * When you compile your game, change the absolute paths to a
             * relative one, and put on the folder of your *.exe, it will work.
             */
            std::string paddle("D:\\pong-game\\res\\icons\\paddle.bmp");
            std::string ball("D:\\pong-game\\res\\icons\\ball.bmp");
            std::string ballSound("D:\\pong-game\\res\\sounds\\ballHit.wav");
        #else //LINUX like.
            std::string paddle("res/icons/paddle.bmp");
            std::string ball("res/icons/ball.bmp");
            std::string ballSound("res/sounds/ballHit.wav");
        #endif

        int32_t ballColorKey[3] = {0x20, 0x20, 0x20};

        Ball ball1(loadBMP(ball, ballColorKey), &windowRenderer,
                   pong.getWidth()/2, pong.getHeight()/2, 10, 10);

        Paddle player1(loadBMP(paddle), &windowRenderer, 6,
                       1, pong.getHeight()/2-(50/2), 10, 50);

        Paddle player2(loadBMP(paddle), &windowRenderer, 6,
                       pong.getWidth()-11, pong.getHeight()/2-(50/2), 10, 50);

        Pong pongPlayer1(&player1, &font, &windowRenderer, fontColor,
                         pong.getWidth()/2-150, pong.getWidth()/2-300);

        Pong pongPlayer2(&player2, &font, &windowRenderer, fontColor,
                         pong.getWidth()/2+100, pong.getWidth()/2-300);

        AudioWrapper gameSound(&effect, &music);

        //works only on linux.
        if(!gameSound.loadEffect(ballSound))
            return 1;

        const Uint8* keyState;

        while(!exit)
        {
            ticksCount = SDL_GetTicks();

            keyState = SDL_GetKeyboardState(NULL);

            /* SDL_GetKeyboardState it's async. that solved the problem of the
             * paddles moving at the same time.
             * Thanks to veQue on IRC!
             */
            if(keyState[SDL_SCANCODE_W])
                playerKeys[0] = true;
            if(keyState[SDL_SCANCODE_S])
                playerKeys[1] = true;
            if(keyState[SDL_SCANCODE_UP])
                playerKeys[2] = true;
            if(keyState[SDL_SCANCODE_DOWN])
                playerKeys[3] = true;

            while(SDL_PollEvent(&event)) {
                switch(event.type) {

                case SDL_QUIT:
                    log("SDL has quited perfectly! :)");
                    exit = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {

                    case SDLK_ESCAPE:
                        exit = true;
                        break;

                    case SDLK_F11:
                        int fullscreenFlag = SDL_GetWindowFlags(window);

                        if((fullscreenFlag & SDL_WINDOW_FULLSCREEN) ==
                            SDL_WINDOW_FULLSCREEN)
                            SDL_SetWindowFullscreen(window, 0);
                        else
                            SDL_SetWindowFullscreen(window,
                                                    SDL_WINDOW_FULLSCREEN);
                        break;
                    }
                }
            }

            /* FIXME: The players has to be able to moviment bot paddles on the
             * same time!
             */
            if(playerKeys[0])
                player1.moveUp();
            if(playerKeys[1])
                player1.moveDown();
            if(playerKeys[2])
                player2.moveUp();
            if(playerKeys[3])
                player2.moveDown();

            ball1.move(player1.getRect(), player2.getRect(), &pong, &gameSound);

            pong.updateGameState(&player1, &player2, &ball1);

            for(int i = 0; i < 4; i++) {
                if(playerKeys[i] == true)
                    playerKeys[i] = false;
            }

            //Rendering everything
            SDL_RenderClear(windowRenderer);
            pongPlayer1.renderScore();
            pongPlayer2.renderScore();
            //renderTexture(loadBMP(paddle), &windowRenderer, 10,
            //              pong.getHeight(), pong.getWidth()/2-(10/2),
            //              0);
            player1.show();
            player2.show();
            ball1.show();

            //updates the screen, like SDL_Flip on SDL 1.2
            SDL_RenderPresent(windowRenderer);

            //Trying to fix the FPS to 60.0
            if(1000/pong.getFPS() > (SDL_GetTicks() - ticksCount))
                SDL_Delay(1000/pong.getFPS()-(SDL_GetTicks() - ticksCount));
        }

    }

    //prevent memory leaks. Newb stuff
    SDL_DestroyRenderer(windowRenderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    SDL_Quit();

    return 0;
}

/**
 * @brief initSDL This function initializes the SDL Window.
 * @param window The window of the game
 * @param windowRenderer A context where everything will be rendered.
 * @param width Size in width of the window
 * @param height Size in height of the window
 * @return A flag which may be true or false depending on the result of the
 * initilization of the SDL.
 */
bool initSDL(SDL_Window** window, SDL_Renderer** windowRenderer,
             const int width, const int height)
{

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        logerr("Could not initialize the video | audio dude :(");
        logerr(SDL_GetError());
        return false;
    }
    else {
        log("SDL Initialized perfectly. :)");
        *window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, width, height,
                                  SDL_WINDOW_SHOWN);

        }

        //Is the window filled?
        if(window == NULL) {
            logerr("Could not create window dude :(");
            logerr(SDL_GetError());
            return false;
        }
        else {
            SDL_ShowCursor(0); //don't show the cursor.

            *windowRenderer = SDL_CreateRenderer(*window, -1,
                                                 SDL_RENDERER_ACCELERATED |
                                                 SDL_RENDERER_PRESENTVSYNC);

            if(windowRenderer == NULL)
                logerr("Window Renderer could not be created :(");
            //Clear the renderer with a drawing color
            else {
                log("Window Renderer created perfectly. :)");
                SDL_SetRenderDrawColor(*windowRenderer, 0x20, 0x20, 0x20, 1);
            }
        }
    return true;
}


bool initFont(TTF_Font** font, SDL_Color* fontColor)
{
    if(TTF_Init() != 0)
    {
        std::cout << "LOG_ERR: Could not initialize TTF" << std::endl;
        return false;
    }
    else
    {
        std::cout << "LOG: TTF Font initialized perfectly! :)" << std::endl;

        #ifdef __WINDOWS__
            std::string fonts[3] =
            {
                "D:\\pong-game\\res\\fonts\\OpenSans-Regular.ttf",
                "D:\\pong-game\\res\\fonts\\OpenSans-Bold.ttf",
                "D:\\pong-game\\res\\fonts\\OpenSans-ExtraBold.ttf"
            };
        #else
            std::string fonts[3] =
            {
                "res/fonts/OpenSans-Regular.ttf",
                "res/fonts/OpenSans-Bold.ttf",
                "res/fonts/OpenSans-ExtraBold.ttf"
            };
        #endif

        *font = TTF_OpenFont(fonts[1].c_str(), 400);

        if(*font == NULL)
        {
            logerr("Loading the font: " + fonts[1] + " failed!");
            logerr(TTF_GetError());
        }
        else
            log("Font: " + fonts[1] + " loaded perfectly! :)");

        //setting the font color.
        fontColor->r = 200;
        fontColor->g = 200;
        fontColor->b = 200;
        fontColor->a = 90;
    }
    return true;
}
