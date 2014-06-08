<b>Pong Game</b>
===

A remake of the <b>Pong Game</b> of Atari(1972) with SDL2! The game has better graphics, but yet, is not so GOOD.

This game was compiled in Linux with G++ and in Windows if MingW32, using the Qt and Code::Blocks, so you may have no problems with these IDEs.

You do <b>need</b> of:
  * <a href="http://www.libsdl.org/download-2.0.php">SDL2</a>
  * <a href="https://www.libsdl.org/projects/SDL_image/">SDL2 Image</a>
  * <a href="https://www.libsdl.org/projects/SDL_ttf/">SDL2 TTF</a>
 

<b>Remind:</b> The res folder has to be on the sae folder as the *.exe , otherwise, it will give you a segmentation fault, or you can change the path to the images and fonts in the main.cpp and recompile the game. If you are having problems executing the game is probably because you don't have the runtime libraries of the SDL2, SDL2_image, SDL2_ttf, so just look at the links above and download them.


This project is licensee on <b><a href="http://www.apache.org/licenses/LICENSE-2.0.html">Apache v2</a></b>!

===
<b>Roadmap:</b> 
  * Better collision detection.
  * Over each "init state" of the game, a random direction for the ball.
  * <s>Ball speed increases over the course of hits in the paddles.</s> (Already done, but it generates other problem, so I'll take a little bit of time to commit the changes)
  * Pause game
  * A GUI menu.
  * AI
  * Lua Script.

===
Contributors
 * Me (Rafael Campos Nunes).


