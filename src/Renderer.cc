#include "Renderer.hh"

#include "DrawingComp.hh"
#include "Texture.hh"

Renderer::Renderer(SDL_Window* window, bool useHardwareAcceleration,
                   bool useVSync) {
  Uint32 flags;
  flags |= (useHardwareAcceleration ? SDL_RENDERER_ACCELERATED : 0);
  flags |= (useVSync ? SDL_RENDERER_PRESENTVSYNC : 0);
  int windowDriverIndex = -1;
  this->renderer = (SDL_CreateRenderer(window, windowDriverIndex, flags));
}

void Renderer::prepare(DrawingComponentSPtr drawable) {
  SDL_Rect renderQuad = {drawable->getX(), drawable->getY(),
                         drawable->getWidth(), drawable->getHeight()};
  SDL_Texture* textureData = drawable->getTexture()->getRawData().get();
  SDL_Rect* clip = drawable->getClippingRectangle();
  Angle angle = drawable->getAngle();
  SDL_RenderCopyEx(this->renderer, textureData, clip, &renderQuad, angle,
                   center, flip);
}

void Renderer::render() { SDL_RenderPresent(this->renderer); }
