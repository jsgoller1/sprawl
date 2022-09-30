# neon-rain
2D cyberpunk game

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
