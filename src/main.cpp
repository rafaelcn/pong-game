/**
  * This project was made with the intuit of learn the general and basic stuff
  * of the SDL2.  This  file  should be clean  and  small (it is NOT SP clean
  * and small), so  I'll  have  to separate  in  various  modules(classes,
  * structs, or any kind of wrapper).
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "game.hpp"

int main(int argc, char* argv[])
{
    Game pong_game;

    while(pong_game.is_running())
    {
        pong_game.update_game();
        pong_game.handle_events();
        pong_game.render_game();
        //ball1.move(player1.getRect(), player2.getRect(), &pong, &gameSound);

        //pong.updateGameState(&player1, &player2, &ball1);

    }

    return 0;
}
