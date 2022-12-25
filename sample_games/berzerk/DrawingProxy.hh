#pragma once

#include "SDL2/SDL.h"

// Forward decls
class Direction;
class Vect2D;

class DrawingProxy {
 public:
  virtual ~DrawingProxy();
  virtual void draw(const Vect2D& center, const int width, const int height, SDL_Surface* surface) = 0;
};
