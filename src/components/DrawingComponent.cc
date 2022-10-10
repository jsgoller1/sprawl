#include "DrawingComponent.hh"

DrawingComponent::DrawingComponent(
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<Texture> texture, const SDL_RendererFlip flip) {
  this->positionComponent = positionComponent;
  this->texture = texture;
  this->flip = flip;
  this->clippingRectangle = nullptr;
  this->angle = 0.0;
}

shared_ptr<Vect2D> DrawingComponent::getDrawPoint() const {
  // Get the specific point SDL should use for drawing; SDL treats
  // this as the top left of the image and draws from there.
  shared_ptr<Vect2D> drawPoint = this->positionComponent->getCenter();
  drawPoint->x -= this->getWidth() / 2;
  // Lower y values are higher on the screen.
  drawPoint->y -= this->getHeight() / 2;
  return drawPoint;
}
