#pragma once
#include <string>

#include "SDL2/SDL.h"
#include "Vect2D.hh"

class Drawable {
 public:
  Drawable(const Vect2D& center, const int height, const int width, const std::string& texturePath);
  virtual ~Drawable();
  int getHeight() const;
  int getWidth() const;
  Vect2D getCenter() const;
  void setCenter(const Vect2D& center);
  void updateCenter(const Vect2D& delta);
  Vect2D getTopLeft() const;
  Vect2D getTopRight() const;
  Vect2D getBottomLeft() const;
  Vect2D getBottomRight() const;

  SDL_Surface* getPixelData() const;
  virtual SDL_Rect getBoundingBox() const;

 private:
  Vect2D _center;
  int _height;
  int _width;
  SDL_Surface* _pixelData;
};
