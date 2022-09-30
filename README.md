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

## Coding conventions
### Use full names and types. 
- `PhysicsManager` is better than `PhysMgr`
- `shared_ptr<PhysicsManager>` is better than `typedef shared_ptr<PhysicsManager> PhysicsManagerSPtr`. 
### Use components 
Neon Rain is modeled after an entity-component system, so consider creating a new component and composing it into GameObject when adding new functionality. Avoid bloating GameObject or using inheiritance. 
### Use const and smart pointers everywhere
- Everything should be const everywhere until proven otherwise. 
- Use smart pointers everywhere a pointer is used. Do not use raw pointers. 
- If you have to use raw pointers to interface with another API (i.e. SDL), do it as close to the API calls as you can, and consider creating a class that will automatically manage the raw pointer, then wrapping that in a smart pointer. 
    - This is especially important for SDL; I once caused a 1 GB / sec memory leak by not cleaning up textures correctly, and my machine hung until the Linux OOM killer killed the program. 
- Use smart pointers over const references when possible. 
- Do not use smart pointers as arguments for operator loading; overloaded operators should work only on const references to objects. 

### Use dependency injection and RAII
- All constructors should follow RAII; a constructor should handle the creation/initialization of all owned objects and attributes
- All objects should have a constructor that supports dependency injection via optional parameters. Prefer dep injection with default parameters resulting in default objects over passing parameters for the construction of owned objects. 
### Try not to put code in headers
The general rule is "header files (`.hh`) describe what something is and what it can do, source files (`.cc`) describe how it does it". Code should usually go into `.cc` files, but some exceptions are acceptable (either for convenience / concision, or because it breaks the general rule):
- Attribute getters and setters that are a single line return or assignment; these should not go in source files unless they're longer than a single line. 
- Static methods that fundamentally change the nature of a class, such as a static `instance()` method for a Singleton class (e.g. `EntityManager`).
- Static methods used in place of constants, e.g. `Direction::Up()`. 
