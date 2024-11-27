#include "game.hpp"

int main(void)
{
    Game pong_game;

    while (pong_game.is_running()) {
      pong_game.run();
    }

    return 0;
}
