# Sprawl game engine
A 2D game engine built to implement __Neon Rain__. 

## Setup
Sprawl requires SDL3 and SDL3_image to run. Instructions for compiling them from source via CMake follow. 

### SDL setup
1. `git clone git@github.com:libsdl-org/SDL.git`
1. `mkdir SDL/build`
1. `cd SDL/build`
1. `cmake path/to/SDL`
1. `make all`
1. `sudo make install`

### SDL_image setup
1. `git clone git@github.com:libsdl-org/SDL_image.git`
1. `mkdir SDL_image/build`
1. `cd SDL_image/build`
1. `cmake path/to/SDL_image`
1. `make all`
1. `sudo make install`

After installing both, you may need to update your shared library cache:
```
sudo ldconfig
```

## Credits, Resources, References
- [LazyFoo's C++ SDL tutorials](https://lazyfoo.net/tutorials/SDL/) were extremely helpful for getting this project off the ground.
- [Game Engine Physics Development by Ian Millington](https://www.amazon.com/Game-Physics-Engine-Development-Commercial-Grade/dp/0123819768/) was super helpful; some of his code was was partially copied and modified to support Neon Rain. 
- [Elliott Jin](https://github.com/robot-dreams) for the advice, rubber-ducking, and reassurance.
- Eric Barone (ConcernedApe), John Carmack, Matt Dabrowski, Terry A. Davis, Paul Erdős, and Richard Feynman for their inspiring examples

## Licensing 
Sprawl is presently released under GPLv3. Sprawl uses C and C++ standard libraries provided by Clang. It also uses or modifies the following:
- `SDL`, released under the [zlib License](https://raw.githubusercontent.com/libsdl-org/SDL/main/LICENSE.txt).
- `cyclone-physics`, released under the [MIT License](https://raw.githubusercontent.com/idmillington/cyclone-physics/master/LICENSE).
- `nlohmann/json`, released under the [MIT License](https://raw.githubusercontent.com/nlohmann/json/develop/LICENSE.MIT).
- `fmt`, released under the [MIT License](https://github.com/fmtlib/fmt/blob/master/LICENSE.rst)
- `rxi/log.c`, released under the [MIT License](https://github.com/rxi/log.c/blob/master/LICENSE)
