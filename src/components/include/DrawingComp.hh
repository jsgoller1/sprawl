#pragma once
#include <SDL2/SDL.h>

#include <vector>

#include "Memory.hh"
#include "PositionComp.hh"
#include "Texture.hh"

using std::vector;

typedef double Angle;

class DrawingComp {
 public:
  DrawingComp(const shared_ptr<PositionComp> positionCompSPtr = nullptr,
              const TextureSPtr texture = nullptr,
              const SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Getters/Setters for owned attributes
  Angle getAngle();
  SDL_RendererFlip getFlip();
  TextureSPtr getTexture();
  void setTexture(const TextureSPtr texture);
  SDL_Rect* getClippingRectangle();

  // Forward to Texture()
  PositionUnit getWidth();
  PositionUnit getHeight();

  // Forward to PositionComp()
  int getX();
  int getY();
  shared_ptr<Vect2D> getCenter();
  shared_ptr<Vect2D> getDrawPoint();

 private:
  shared_ptr<PositionComp> positionCompSPtr;
  TextureSPtr texture;
  SDL_RendererFlip flip;
  SDL_Rect* clippingRectangle;
  Angle angle;
};

typedef shared_ptr<DrawingComp> DrawingCompSPtr;
typedef vector<shared_ptr<DrawingComp>> DrawingComponentSPtrCollection;
typedef shared_ptr<vector<shared_ptr<DrawingComp>>>
    DrawingCompSPtrCollectionSPtr;
