#pragma once

#include "SDL2/SDL.h"

// Forward decl
class Vect2D;

class Screen {
 public:
  Screen(const int width, const int height);
  ~Screen();
  void prepare(const Vect2D& center, const int height, const int width, SDL_Surface* texture);

  void draw();
  void clear();

  int getHeight() const;
  int getWidth() const;

  Vect2D getTopLeft() const;
  Vect2D getTopRight() const;
  Vect2D getBottomLeft() const;
  Vect2D getBottomRight() const;

  Vect2D toScreenCoordinates(const Vect2D& center) const;
  Vect2D toWorldCoordinates(const Vect2D& vect) const;

 private:
  int _width;
  int _height;
  SDL_Window* _window;
  SDL_Renderer* _renderer;
  Vect2D getDrawPoint(const Vect2D& center, const int height, const int width) const;
  void printSDLError();
};
