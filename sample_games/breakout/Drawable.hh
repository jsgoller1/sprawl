#pragma once
#include <string>

#include "SDL2/SDL.h"
#include "Vect2D.hh"

class Drawable {
 public:
  Drawable(const Vect2D& center, const int height, const int width, const std::string& texturePath);
  virtual ~Drawable();
  void updateCenter(const Vect2D& delta);
  void setCenter(const Vect2D& center);
  Vect2D getCenter() const;
  Vect2D getTopLeft() const;
  int getHeight() const;
  int getWidth() const;
  SDL_Surface* getPixelData() const;
  virtual SDL_Rect getBoundingBox() const;

 private:
  Vect2D _center;
  int _height;
  int _width;
  SDL_Surface* _pixelData;
};
