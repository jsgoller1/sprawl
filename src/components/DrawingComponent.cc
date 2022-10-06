#include "DrawingComponent.hh"

DrawingComponent::DrawingComponent(const shared_ptr<Identity> ownerIdentity,
                                   const shared_ptr<PositionComponent> positionComponent,
                                   const shared_ptr<Texture> texture, const SDL_RendererFlip flip)
    : Component(ownerIdentity) {
  this->positionComponent = positionComponent;
  this->texture = texture;
  this->flip = flip;
  this->clippingRectangle = nullptr;
  this->angle = 0.0;
}

Vect2D DrawingComponent::getDrawPoint() const {
  // Get the specific point SDL should use for drawing; SDL treats
  // this as the top left of the image and draws from there. We do not
  // need to account for other SDL specifics here (i.e. y-axis flip or top left
  // corner.)
  Vect2D drawPoint = this->positionComponent->getCenter();
  drawPoint.x(drawPoint.x() - this->getWidth() / 2);
  drawPoint.y(drawPoint.y() + this->getHeight() / 2);
  return drawPoint;
}
