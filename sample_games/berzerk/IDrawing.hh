#pragma once
#include <memory>
#include <string>

#include "DrawingProxy.hh"
#include "SDL2/SDL.h"
#include "Vect2D.hh"

class IDrawing {
 public:
  IDrawing(const Vect2D& center, const int height, const int width, const std::string& texturePath,
           const std::shared_ptr<DrawingProxy> drawingProxy);
  virtual ~IDrawing();
  int getHeight() const;
  int getWidth() const;
  Vect2D getCenter() const;
  void setCenter(const Vect2D& center);
  void updateCenter(const Vect2D& delta);
  Vect2D getTopLeft() const;
  // Vect2D getTopRight() const;
  // Vect2D getBottomLeft() const;
  // Vect2D getBottomRight() const;
  // SDL_Surface* getPixelData() const;
  void draw() const;

 private:
  std::shared_ptr<DrawingProxy> _drawingProxy;
  Vect2D _center;
  int _height;
  int _width;
  SDL_Surface* _pixelData;
};
