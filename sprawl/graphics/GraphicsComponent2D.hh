#pragma once

#include "Math.hh"
#include "PositionComponent.hh"
#include "SDL3/SDL.h"
#include "Texture.hh"
#include "Types.hh"

static constexpr char DRAWING_COMPONENT_NAME[] = "GraphicsComponent2D";

typedef double Angle;
typedef int GraphicsLayer;

class Actor;

class GraphicsComponent2D : public Component {
 public:
  GraphicsComponent2D(const std::shared_ptr<Texture> texture = nullptr, const SDL_RendererFlip flip = SDL_FLIP_NONE);
  ~GraphicsComponent2D() override;

  std::string toString() const override;
  void managerRegister() override;
  void managerUnregister() override;

  // Accessors for components
  std::shared_ptr<Texture> getTexture() const;
  void setTexture(const std::shared_ptr<Texture> texture);

  // Forwards to Texture
  PositionUnit getWidth() const;
  PositionUnit getHeight() const;

  // Accessors for attributes
  Angle getAngle() const;
  void setAngle(const Angle angle);
  SDL_RendererFlip getFlip() const;
  void setFlip(const SDL_RendererFlip flip);
  SDL_Rect* getClippingRectangle() const;
  void setClippingRectangle(SDL_Rect* const clippingRectangle);

 private:
  std::shared_ptr<Texture> texture;
  Angle angle;
  SDL_Rect* clippingRectangle;
  SDL_RendererFlip flip;
};
