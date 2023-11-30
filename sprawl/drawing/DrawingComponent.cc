#include "DrawingComponent.hh"

#include "Actor.hh"
#include "DrawingManager.hh"

DrawingComponent::DrawingComponent(const std::weak_ptr<Actor> owner, const std::shared_ptr<Texture> texture,
                                   const SDL_RendererFlip flip)
    : Component(owner) {
  DrawingManager::instance().manage(this->getOwner());
  this->texture = texture;
  this->flip = flip;
  this->clippingRectangle = nullptr;
  this->angle = 0.0;
}

DrawingComponent::~DrawingComponent() { DrawingManager::instance().unmanage(this->getOwner()); }

std::string DrawingComponent::toString() const {
  return fmt::format("DrawingComponent({})", this->getOwner()->toString());
}

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
