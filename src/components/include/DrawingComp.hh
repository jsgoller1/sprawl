#pragma once
#include <SDL2/SDL.h>

#include <vector>

#include "Memory.hh"
#include "PositionComp.hh"
#include "Texture.hh"

using std::vector;

typedef double Angle;
typedef SDL_Point Point;

class DrawingComp {
 public:
  DrawingComp(const PositionCompSPtr positionCompSPtr = nullptr,
              const TextureSPtr textureSPtr = nullptr,
              const PointSPtr center = nullptr,
              const SDL_RendererFlip flip = SDL_FLIP_NONE);
  // Forward to Texture()
  TextureSPtr getTexture();
  SDL_Rect* getClippingRectangle();

  // Forward to PositionComp()
  int getX();
  int getY();

  PositionUnit getWidth();
  PositionUnit getHeight();
  Angle getAngle();
  PointSPtr getCenter();
  SDL_RendererFlip getFlip();

 private:
  PositionCompSPtr positionCompSPtr;
  TextureSPtr textureSPtr;
  PointSPtr center;
  SDL_RendererFlip flip;
  SDL_Rect* clippingRectangle;
  Angle angle;
};

typedef shared_ptr<DrawingComp> DrawingCompSPtr;
typedef vector<shared_ptr<DrawingComp>> DrawingComponentSPtrCollection;
typedef shared_ptr<vector<shared_ptr<DrawingComp>>>
    DrawingCompSPtrCollectionSPtr;
