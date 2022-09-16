#include "DrawingComp.hh"

DrawingComp::DrawingComp(const PositionCompSPtr positionCompSPtr,
                         const TextureSPtr textureSPtr, const PointSPtr center,
                         const PositionUnit width, const PositionUnit height,
                         const SDL_RendererFlip flip) {
  this->positionCompSPtr = positionCompSPtr;
  this->textureSPtr = textureSPtr;
  this->center = center;
  this->width = width;
  this->height = height;
  this->flip = flip;
}

TextureSPtr DrawingComp::getTexture() { return this->textureSPtr; }
SDL_Rect* DrawingComp::getClippingRectangle() {
  return this->clippingRectangle;
}

PositionUnit DrawingComp::getX() { return this->positionCompSPtr->getX(); }
PositionUnit DrawingComp::getY() { return this->positionCompSPtr->getY(); }
PositionUnit DrawingComp::getWidth() { return this->width; }
PositionUnit DrawingComp::getHeight() { return this->height; }
SDL_RendererFlip DrawingComp::getFlip() { return this->flip; }
Angle DrawingComp::getAngle() { return this->angle; }
PointSPtr DrawingComp::getCenter() { return this->center; }
