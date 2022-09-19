#include "DrawingComp.hh"

DrawingComp::DrawingComp(const PositionCompSPtr positionCompSPtr,
                         const TextureSPtr textureSPtr,
                         const SDL_RendererFlip flip) {
  this->positionCompSPtr = positionCompSPtr;
  this->textureSPtr = textureSPtr;
  this->flip = flip;
  this->clippingRectangle = nullptr;
}

TextureSPtr DrawingComp::getTexture() { return this->textureSPtr; }

// TODO: Clipping rectangle, flip, and angle should probably belong to Texture.
SDL_Rect* DrawingComp::getClippingRectangle() {
  return this->clippingRectangle;
}
SDL_RendererFlip DrawingComp::getFlip() { return this->flip; }
Angle DrawingComp::getAngle() { return this->angle; }

// Forwarding methods
PositionUnit DrawingComp::getWidth() { return this->textureSPtr->getWidth(); }
PositionUnit DrawingComp::getHeight() { return this->textureSPtr->getHeight(); }
PointSPtr DrawingComp::getCenter() {
  return this->positionCompSPtr->getCenter();
}
PositionUnit DrawingComp::getX() { return this->positionCompSPtr->getX(); }
PositionUnit DrawingComp::getY() { return this->positionCompSPtr->getY(); }
