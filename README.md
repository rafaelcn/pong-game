__Pong Game__
===

A remake of the __Pong Game__ of Atari(1972) with SDL2! The game has better graphics, but yet, is not so GOOD.

![Game Image](PongGame.png)

This game was compiled in Linux with G++ and in Windows if MingW32, using the Qt and Code::Blocks, so you may have no problems with these IDEs.

You do <b>need</b> of:
  * [SDL2](http://www.libsdl.org/download-2.0.php)
  * [SDL2 Image](https://www.libsdl.org/projects/SDL_image/)
  * [SDL2 TTF](https://www.libsdl.org/projects/SDL_ttf/)
 

<b>Remind:</b> The res folder has to be on the sae folder as the *.exe , otherwise, it will give you a segmentation fault, or you can change the path to the images and fonts in the main.cpp and recompile the game. If you are having problems executing the game is probably because you don't have the runtime libraries of the SDL2, SDL2_image, SDL2_ttf, so just look at the links above and download them.


This project is licensee on __[Apache v2](http://www.apache.org/licenses/LICENSE-2.0.html)__!

===
<b>Roadmap:</b> 
  - [ ] __Perfect__ collision detection.
  - [ ] Over each "init state" of the game, a random direction for the ball.
  - [x] Ball speed increases over the course of hits in the paddles. (Already done, but it generates other problem, so I'll take a little bit of time to commit the changes)
  - [ ] AI
  - [ ] Pause game
  - [ ] A GUI menu.
  - [ ] Lua Script.

===
Contributors
 * Me (Rafael Campos Nunes).


