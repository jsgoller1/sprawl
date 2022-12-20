#pragma once
#include <string>

#include "SDL2/SDL.h"
#include "Vect2D.hh"

class Drawable {
 public:
  Drawable(const Vect2D& center, const int height, const int width, const std::string& texturePath);
  virtual ~Drawable();

  void setCenter(const Vect2D& center);
  Vect2D getCenter() const;
  int getHeight() const;
  int getWidth() const;
  SDL_Surface* getPixelData() const;

 private:
  Vect2D _center;
  int _height;
  int _width;
  SDL_Surface* _pixelData;
};
