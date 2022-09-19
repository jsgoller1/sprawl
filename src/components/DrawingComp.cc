#include "DrawingComp.hh"

DrawingComp::DrawingComp(const PositionCompSPtr positionCompSPtr,
                         const TextureSPtr textureSPtr, const PointSPtr center,
                         const SDL_RendererFlip flip) {
  this->positionCompSPtr = positionCompSPtr;
  this->textureSPtr = textureSPtr;
  this->center = center;
  this->flip = flip;
}

TextureSPtr DrawingComp::getTexture() { return this->textureSPtr; }
SDL_Rect* DrawingComp::getClippingRectangle() {
  return this->clippingRectangle;
}

PositionUnit DrawingComp::getX() { return this->positionCompSPtr->getX(); }
PositionUnit DrawingComp::getY() { return this->positionCompSPtr->getY(); }
PositionUnit DrawingComp::getWidth() { return this->textureSPtr->getWidth(); }
PositionUnit DrawingComp::getHeight() { return this->textureSPtr->getHeight(); }
SDL_RendererFlip DrawingComp::getFlip() { return this->flip; }
Angle DrawingComp::getAngle() { return this->angle; }
PointSPtr DrawingComp::getCenter() { return this->center; }
