#### TETRIS SDL

### PROJECT INFORMATION

This Project holds Tetris implementet after the NES version from 1989.
The game features a save System for highscores, a timer to show currently played time,
via command line argument 2 one can set the start level to any given int,
current score, a level System reminicant of the level System in the 1989 version,
pause functionallity and through the 3 and 4 argument the rotational keys can be set via a 1 char argument ( currently doesen't work as any keybindings need to be constexpr and can therefor not be set at runtime).

### Expiriences

Sadly I noticed the problem of dynamicly binding keys in SDL2 at the very end,
so I wasn't able to switch to openGL in time.
The memory leaks I have are weird and realy shouldnt happen, I have been able to narrow them down to the renderer, window or SDL instance.
But all of these instances are closed correctly, it might be a problem with the SDL library itself.
I choose a different Keyboard layout and hope that is no problem,
it can easely be fixed by changing the SDLK_ keys.

The text scaling isn't optimal but still very much readable.
I made no test for the speed of the tetromino falling as it can simply
be read from the update cap that I'm displaying in the console.
The speed isn't exactly the right speed but ever so slightly off at some point space.
I'm not sure if it would even be possible to get it exactly to the speed.

I documented the Project extansivly and hope the code is understandable.
I think I didn't do anything to complex and it should be easaly readable.

### CONTROLS

a, d : Move left/right
space: Pause/Unpause/start Game
q, e: Rotate left/right ( standart configuration )

### KNOWN ISSUES

If the save_data.txt file exists, but does not hold a single int,
the game will automaticlly crash.

Keys can not be rebinded at runtime, I couldnt fix the problem and could find anything on the topic online.
A possibillity would have been to make preset layouts, but that wouldn't have fullfilled the requierment either.

There are 3 memory leaks connected to the renderer, window and SDL_INIT.
But I cant find the issue with the initialization.

The text scaling is a bit off, due to time constrains I have not been able to work
the scaling out.

### INSTALLATION

Befor making the game via make in the /src directory. 
Make sure SDL2 is installt on your computer.

## SDL2 Setup

# Linux

Either via git clone and building:

git clone https://github.com/libsdl-org/SDL.git -b SDL2
cd SDL
mkdir build
cd build
../configure
make
sudo make install

Or via the terminal:

Debian/Ubuntu

sudo apt-get install libsdl2-dev

Fedora/CentOS

yum search SDL2-devel

# WINDOWS

Please visit the official SDL2 Installation guide for more information:
https://wiki.libsdl.org/SDL2/Installation

## RUN GAME

Navigate to the /src directory and:

make game

To run the game execute the GameMain file