#include "DrawingComponent.hh"

#include "Actor.hh"
#include "DrawingManager.hh"

DrawingComponent::DrawingComponent(const std::shared_ptr<Texture> texture, const SDL_RendererFlip flip) : Component() {
  this->texture = texture;
  this->flip = flip;
  this->clippingRectangle = nullptr;
  this->angle = 0.0;
}

DrawingComponent::~DrawingComponent() { this->managerUnregister(); }

std::string DrawingComponent::toString() const {
  return fmt::format("DrawingComponent({})", this->getOwner()->toString());
}

void DrawingComponent::managerRegister() { DrawingManager::instance().manage(this->getOwner()); }
void DrawingComponent::managerUnregister() { DrawingManager::instance().unmanage(this->getOwner()); }

std::shared_ptr<Texture> DrawingComponent::getTexture() const { return this->texture; }
void DrawingComponent::setTexture(const std::shared_ptr<Texture> texture) { this->texture = texture; }

// Forwards to Texture
PositionUnit DrawingComponent::getWidth() const { return this->texture->getWidth(); }
PositionUnit DrawingComponent::getHeight() const { return this->texture->getHeight(); }

// Accessors for attributes
Angle DrawingComponent::getAngle() const { return this->angle; }
void DrawingComponent::setAngle(const Angle angle) { this->angle = angle; }
SDL_RendererFlip DrawingComponent::getFlip() const { return this->flip; }
void DrawingComponent::setFlip(const SDL_RendererFlip flip) { this->flip = flip; }
SDL_Rect* DrawingComponent::getClippingRectangle() const { return this->clippingRectangle; }
void DrawingComponent::setClippingRectangle(SDL_Rect* const clippingRectangle) {
  this->clippingRectangle = clippingRectangle;
}
