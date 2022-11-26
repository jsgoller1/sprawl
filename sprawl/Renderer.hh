#pragma once

#include "DrawingComponent.hh"
#include "Logging.hh"
#include "SDL2/SDL.h"
#include "Texture.hh"
#include "Types.hh"

class Renderer {
 public:
  Renderer(const ScreenWidth screenWidth, const ScreenHeight height, SDL_Window* const window,
           const bool useHardwareAcceleration, const bool useVSync);

  void prepare(const std::shared_ptr<DrawingComponent> drawable) const;
  void render() const;
  void clear() const;
  Vect2D toScreenCoordinates(const Vect2D& vect) const;

 private:
  ScreenWidth _screenWidth;
  ScreenHeight _screenHeight;
  SDL_Renderer* renderer;
  SDL_Texture* prepareTexture(const std::shared_ptr<Texture> texture) const;
};
