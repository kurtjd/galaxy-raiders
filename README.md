# space-invaders

![Space Invaders](/misc/screenshot.png?raw=true "Space Invaders")

This is a Space Invaders clone written in C++ and SFML. I wanted to make it a pretty faithful copy, so there are no "enhancements" on my part. However, it does have some of the gameplay tricks of the original such as the 300 point UFO trick, the "lasers don't hurt you when shot by Invaders right above the invasion line" trick, etc.

I learned a lot about C++ and OOP as I wrote this, so unfortunately code started to get spaghettified as I realized my original class setup didn't work well on a large scale, and I eventually got tired of trying to refactor everything. Specifically, the game.cpp file got really out of hand as I started implementing states. Still, I consider the structure of the code an improvement on my previous graphical game, Pong, which was written in Python.

Build Procedures
----------------

This project uses the CMake build tool and depends on SFML 2.x and a modern C++ compiler. Building
on Linux, for example:

```
mkdir build && cd build
cmake ../cmake/
make
```

What I Learned and What I Plan to do Differently Next Game
----------------------------------------------------------
-Decouple graphics from gameplay logic. Although it isn't absolutely terrible in my code, it can still be much better.

-Make objects not so tightly coupled. This was increasing compile times. Forward declare classes instead of including their header file when able.

-Look into game programming patterns, specifically entity-component pattern. I really don't like how I'm passing all the game objects separately into each function. There needs to be an easier way to handle all this.

-Implement sprite batching. Although it isn't a big deal here because of the few number of sprites, making individual draw calls for every sprite every frame is very inefficient.

-Make game speed independent of FPS. At first I didn't really understand "delta time", but now that I do, all movements, update ticks, etc should take into account delta time. Having said that, don't use sleep()... really only did this out of laziness.

-Figure out a better way to load and manage resources (IE: textures, sounds, etc). I know my method will fall apart once you have a larger amount of resources.
