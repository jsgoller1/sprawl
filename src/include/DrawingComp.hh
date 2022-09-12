#pragma once
#include <SDL2/SDL.h>

#include <vector>

#include "Memory.hh"
#include "PositionMgr.hh"
#include "Texture.hh"

typedef double Angle;
typedef SDL_Point Point;

class DrawingComponent {
 public:
  DrawingComponent(const PositionMgrSPtr positionMgr);
  // Forward to Texture()
  TextureSPtr getTexture();
  SDL_Rect* getClippingRectangle();

  // Forward to PositionMgr()
  int getX();
  int getY();
  int getWidth();
  int getHeight();

  Angle getAngle();

 private:
  PositionMgrSPtr positionMgr;
  TextureSPtr texture;
};

typedef shared_ptr<DrawingComponent> DrawingComponentSPtr;
typedef std::vector<shared_ptr<DrawingComponent>>
    DrawingComponentSPtrCollection;
typedef shared_ptr<std::vector<shared_ptr<DrawingComponent>>>
    DrawingComponentSPtrCollectionSPtr;
