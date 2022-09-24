#include "DrawingComp.hh"

DrawingComp::DrawingComp(const shared_ptr<PositionComp> positionCompSPtr,
                         const TextureSPtr texture,
                         const SDL_RendererFlip flip) {
  this->positionCompSPtr = positionCompSPtr;
  this->texture = texture;
  this->flip = flip;
  this->clippingRectangle = nullptr;
  this->angle = 0.0;
}

void DrawingComp::setTexture(const TextureSPtr texture) {
  this->texture = texture;
}
TextureSPtr DrawingComp::getTexture() { return this->texture; }

// TODO: Clipping rectangle, flip, and angle should probably belong to Texture.
SDL_Rect* DrawingComp::getClippingRectangle() {
  return this->clippingRectangle;
}
SDL_RendererFlip DrawingComp::getFlip() { return this->flip; }
Angle DrawingComp::getAngle() { return this->angle; }

// Forwarding methods
PositionUnit DrawingComp::getWidth() { return this->texture->getWidth(); }
PositionUnit DrawingComp::getHeight() { return this->texture->getHeight(); }
shared_ptr<Vect2D> DrawingComp::getCenter() {
  return this->positionCompSPtr->getCenter();
}
shared_ptr<Vect2D> DrawingComp::getDrawPoint() {
  // Get the specific point SDL should use for drawing; SDL treats
  // this as the top left of the image and draws from there.
  shared_ptr<Vect2D> drawPoint = this->positionCompSPtr->getCenter();
  drawPoint->x -= this->getWidth() / 2;
  // Lower y values are higher on the screen.
  drawPoint->y -= this->getHeight() / 2;
  return drawPoint;
}

PositionUnit DrawingComp::getX() { return this->positionCompSPtr->getX(); }
PositionUnit DrawingComp::getY() { return this->positionCompSPtr->getY(); }
