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
  std::shared_ptr<PositionComponent> getPositionComponent() const;
  void setPositionComponent(const std::shared_ptr<PositionComponent> positionComponent);
  std::shared_ptr<Texture> getTexture() const;
  void setTexture(const std::shared_ptr<Texture> texture);

  // Forwards to Texture
  PositionUnit getWidth() const;
  PositionUnit getHeight() const;

  // Forwards to PositionComponent
  real getX() const;
  real getY() const;
  Vect2D getCenter() const;

  // Accessors for attributes
  Angle getAngle() const;
  void setAngle(const Angle angle);
  SDL_RendererFlip getFlip() const;
  void setFlip(const SDL_RendererFlip flip);
  SDL_Rect* getClippingRectangle() const;
  void setClippingRectangle(SDL_Rect* const clippingRectangle);

  // Unique methods
  Vect2D getDrawPoint() const;

 private:
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<Texture> texture;

  Angle angle;
  SDL_Rect* clippingRectangle;
  SDL_RendererFlip flip;
};
