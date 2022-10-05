#pragma once

#include "DrawingComponent.hh"
#include "Logger.hh"
#include "Memory.hh"
#include "Texture.hh"
#include "Types.hh"

class Renderer {
 public:
  Renderer(SDL_Window* const window, const bool useHardwareAcceleration,
           const bool useVSync);

  void prepare(const shared_ptr<DrawingComponent> drawable) const;
  void render() const;
  void clear() const;

 private:
  SDL_Renderer* renderer;
  SDL_Texture* prepareTexture(const shared_ptr<Texture> texture) const;
};
