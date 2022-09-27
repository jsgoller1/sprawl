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

## Naming conventions for class/type names
These are for convenience only
- `^.*UPtr$`: a `std::uniq_ptr`.
- `^.*SPtr$`: a `std::shared_ptr`. 
- `^.*Comp$`: a component class for implementing reusable behavior via composition; always access these via smart pointers.
- `^.*Mgr$`: a manager class that stores references to components and updates the owner object through them. 


## Credits, Resources, References
- [LazyFoo's C++ SDL tutorials](https://lazyfoo.net/tutorials/SDL/) were extremely helpful for getting this project off the ground.
- [Game Engine Physics Development by Ian Millington](https://www.amazon.com/Game-Physics-Engine-Development-Commercial-Grade/dp/0123819768/)
- Millington's [cyclone-physics](https://github.com/idmillington/cyclone-physics) engine was partially copied and modified to support Neon Rain. `cyclone-physics` is released under the [MIT License](https://raw.githubusercontent.com/idmillington/cyclone-physics/master/LICENSE).
- [Elliott Jin](https://github.com/robot-dreams) for the advice, rubber-ducking, and reassurance
- Eric Barone (ConcernedApe), John Carmack, Matt Dabrowski, Terry A. Davis, Paul Erdős, and Richard Feynman for their inspiring examples
