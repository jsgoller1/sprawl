#pragma once

#include <SDL2/SDL.h>

#include "Entity.hh"
#include "Math.hh"
#include "PositionComponent.hh"
#include "Texture.hh"
#include "Types.hh"

typedef double Angle;

class DrawingComponent : public Component {
 public:
  DrawingComponent(const std::shared_ptr<Identity> ownerIdentity,
                   const std::shared_ptr<PositionComponent> positionComponent,
                   const std::shared_ptr<Texture> texture = nullptr, const SDL_RendererFlip flip = SDL_FLIP_NONE);

  // Accessors for components
  std::shared_ptr<PositionComponent> getPositionComponent() const { return this->positionComponent; }
  void setPositionComponent(const std::shared_ptr<PositionComponent> positionComponent) {
    this->positionComponent = positionComponent;
  }
  std::shared_ptr<Texture> getTexture() const { return this->texture; }
  void setTexture(const std::shared_ptr<Texture> texture) { this->texture = texture; }

  // Forwards to Texture
  PositionUnit getWidth() const { return this->texture->getWidth(); }
  PositionUnit getHeight() const { return this->texture->getHeight(); }

  // Forwards to PositionComponent
  real getX() const { return this->positionComponent->x(); }
  real getY() const { return this->positionComponent->y(); }
  Vect2D getCenter() const { return this->positionComponent->getCenter(); }

  // Accessors for attributes
  Angle getAngle() const { return this->angle; }
  void setAngle(const Angle angle) { this->angle = angle; }
  SDL_RendererFlip getFlip() const { return this->flip; }
  void setFlip(const SDL_RendererFlip flip) { this->flip = flip; }
  SDL_Rect* getClippingRectangle() const { return this->clippingRectangle; }
  void setClippingRectangle(SDL_Rect* const clippingRectangle) { this->clippingRectangle = clippingRectangle; }

  // Unique methods
  Vect2D getDrawPoint() const;

 private:
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<Texture> texture;

  Angle angle;
  SDL_Rect* clippingRectangle;
  SDL_RendererFlip flip;
};
