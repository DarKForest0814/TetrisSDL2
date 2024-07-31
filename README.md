# TETRIS SDL
- - - -

## PROJECT INFORMATION

This Project holds Tetris implementet after the NES version from 1989.
The game features a save System for highscores, a timer to show currently played time,
via command line argument 2 one can set the start level to any given int,
current score, a level System reminicant of the level System in the 1989 version,
pause functionallity and through the 3 and 4 argument the rotational keys can be set via a 1 char argument ( currently doesen't work as any keybindings need to be constexpr and can therefor not be set at runtime).

## CONTROLS

a, d : Move left/right

space: Pause/Unpause/start Game

q, e: Rotate left/right ( standart configuration )


## KNOWN ISSUES

If the save_data.txt file exists, but does not hold a single int,
the game will automaticlly crash.

There are 3 memory leaks connected to the renderer, window and SDL_INIT.
But I cant find the issue with the initialization.

## INSTALLATION

Befor making the game via make in the /src directory. 
Make sure SDL2 is installt on your computer.

## SDL2 Setup

### Linux

Either via git clone and building:

`git clone https://github.com/libsdl-org/SDL.git -b SDL2`

`cd SDL`

`mkdir build`

`cd build`

`../configure`

`make`

`sudo make install`

Or via the terminal:

Debian/Ubuntu

`sudo apt-get install libsdl2-dev`

Fedora/CentOS

`yum search SDL2-devel`

### WINDOWS

Please visit the official SDL2 Installation guide for more information:
https://wiki.libsdl.org/SDL2/Installation

## RUN GAME

Navigate to the /src directory and:

`make game`

To run the game execute the GameMain file