#include "Actor.hh"
#include "GraphicsComponent2D.hh"
#include "GraphicsManager2D.hh"

GraphicsComponent2D::GraphicsComponent2D(const std::shared_ptr<Texture> texture, const SDL_RendererFlip flip)
    : Component() {
  this->texture = texture;
  this->flip = flip;
  this->clippingRectangle = nullptr;
  this->angle = 0.0;
}

GraphicsComponent2D::~GraphicsComponent2D() { this->managerUnregister(); }

std::string GraphicsComponent2D::toString() const {
  return fmt::format("GraphicsComponent2D({})", this->getOwner()->toString());
}

void GraphicsComponent2D::managerRegister() { GraphicsManager2D::instance().manage(this->getOwner()); }
void GraphicsComponent2D::managerUnregister() { GraphicsManager2D::instance().unmanage(this->getOwner()); }

std::shared_ptr<Texture> GraphicsComponent2D::getTexture() const { return this->texture; }
void GraphicsComponent2D::setTexture(const std::shared_ptr<Texture> texture) { this->texture = texture; }

// Forwards to Texture
PositionUnit GraphicsComponent2D::getWidth() const { return this->texture->getWidth(); }
PositionUnit GraphicsComponent2D::getHeight() const { return this->texture->getHeight(); }

// Accessors for attributes
Angle GraphicsComponent2D::getAngle() const { return this->angle; }
void GraphicsComponent2D::setAngle(const Angle angle) { this->angle = angle; }
SDL_RendererFlip GraphicsComponent2D::getFlip() const { return this->flip; }
void GraphicsComponent2D::setFlip(const SDL_RendererFlip flip) { this->flip = flip; }
SDL_Rect* GraphicsComponent2D::getClippingRectangle() const { return this->clippingRectangle; }
void GraphicsComponent2D::setClippingRectangle(SDL_Rect* const clippingRectangle) {
  this->clippingRectangle = clippingRectangle;
}
