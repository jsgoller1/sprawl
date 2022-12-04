#include "DrawingComponent.hh"

DrawingComponent::DrawingComponent(const std::shared_ptr<Identity> ownerIdentity,
                                   const std::shared_ptr<PositionComponent> positionComponent,
                                   const std::shared_ptr<Texture> texture, const SDL_RendererFlip flip)
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
  Vect2D drawPoint = Vect2D::zero();
  if (this->positionComponent == nullptr) {
    // TODO: This is a useless error message without a reliable way to log which component generates it, which we
    // currently cannot do.
    LOG_ERROR_SYS(LoggingSubsystem::RENDERING, "No PositionComponent for DrawingComponent; rendering to (0,0)");
  } else {
    drawPoint = this->positionComponent->getCenter();
  }
  drawPoint.x(drawPoint.x() - this->getWidth() / 2);
  drawPoint.y(drawPoint.y() + this->getHeight() / 2);
  return drawPoint;
}

std::shared_ptr<PositionComponent> DrawingComponent::getPositionComponent() const { return this->positionComponent; }
void DrawingComponent::setPositionComponent(const std::shared_ptr<PositionComponent> positionComponent) {
  this->positionComponent = positionComponent;
}
std::shared_ptr<Texture> DrawingComponent::getTexture() const { return this->texture; }
void DrawingComponent::setTexture(const std::shared_ptr<Texture> texture) { this->texture = texture; }

// Forwards to Texture
PositionUnit DrawingComponent::getWidth() const { return this->texture->getWidth(); }
PositionUnit DrawingComponent::getHeight() const { return this->texture->getHeight(); }

// Forwards to PositionComponent
real DrawingComponent::getX() const { return this->positionComponent->x(); }
real DrawingComponent::getY() const { return this->positionComponent->y(); }
Vect2D DrawingComponent::getCenter() const { return this->positionComponent->getCenter(); }

// Accessors for attributes
Angle DrawingComponent::getAngle() const { return this->angle; }
void DrawingComponent::setAngle(const Angle angle) { this->angle = angle; }
SDL_RendererFlip DrawingComponent::getFlip() const { return this->flip; }
void DrawingComponent::setFlip(const SDL_RendererFlip flip) { this->flip = flip; }
SDL_Rect* DrawingComponent::getClippingRectangle() const { return this->clippingRectangle; }
void DrawingComponent::setClippingRectangle(SDL_Rect* const clippingRectangle) {
  this->clippingRectangle = clippingRectangle;
}
