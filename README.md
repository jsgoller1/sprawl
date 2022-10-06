# Sprawl game engine
A 2D game engine built to implement __Neon Rain__. 

## Setup
Linux only development at present; requires `make`.

### 1) Install tools
For clang, valgrind, etc.
`sudo make install-devtools`

### 2) Install SDL2
`sudo apt-get install libsdl2-dev`

### 3) Install SDL2_image
Download and unzip [the source](https://github.com/libsdl-org/SDL_image/releases/download/release-2.6.2/SDL2_image-2.6.2.zip). Then inside the directory, run:
```
./configure
make
sudo make install
```

## Credits, Resources, References
- [LazyFoo's C++ SDL tutorials](https://lazyfoo.net/tutorials/SDL/) were extremely helpful for getting this project off the ground.
- [Game Engine Physics Development by Ian Millington](https://www.amazon.com/Game-Physics-Engine-Development-Commercial-Grade/dp/0123819768/) was super helpful; some of his code was was partially copied and modified to support Neon Rain. 
- [Elliott Jin](https://github.com/robot-dreams) for the advice, rubber-ducking, and reassurance.
- Eric Barone (ConcernedApe), John Carmack, Matt Dabrowski, Terry A. Davis, Paul Erdős, and Richard Feynman for their inspiring examples

## Licensing 
Sprawl is presently proprietary / closed source, and may not be bought, sold, reproduced, etc in any capacity without the author's permission. Sprawl uses C and C++ standard libraries provided by Clang. It also makes use of the following:
- `SDL`, released under the [zlib license](https://raw.githubusercontent.com/libsdl-org/SDL/main/LICENSE.txt).
- `cyclone-physics`, released under the [MIT License](https://raw.githubusercontent.com/idmillington/cyclone-physics/master/LICENSE).
- `nlohmann/json`, released under the [MIT License](https://raw.githubusercontent.com/nlohmann/json/develop/LICENSE.MIT).
