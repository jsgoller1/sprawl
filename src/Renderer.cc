#include "Renderer.hh"

#include "DrawingComp.hh"
#include "Logger.hh"
#include "Texture.hh"

Renderer::Renderer(SDL_Window* window, bool useHardwareAcceleration,
                   bool useVSync) {
  Uint32 flags = 0;
  flags |= (useHardwareAcceleration ? SDL_RENDERER_ACCELERATED : 0);
  flags |= (useVSync ? SDL_RENDERER_PRESENTVSYNC : 0);
  int windowDriverIndex = -1;
  this->renderer = (SDL_CreateRenderer(window, windowDriverIndex, flags));
  if (this->renderer == nullptr) {
    logSDLError(SDL_ERROR_OCCURRED, "Renderer::Renderer()");
  }
}

void Renderer::prepare(DrawingCompSPtr drawable) {
  /* Takes a DrawingComponent and prepares it off-screen for rendering.
   */

  SDL_Rect renderQuad = {drawable->getX(), drawable->getY(),
                         drawable->getWidth(), drawable->getHeight()};
  SDL_Texture* textureData = this->prepareTexture(drawable->getTexture());
  SDL_Rect* clip = drawable->getClippingRectangle();
  Angle angle = drawable->getAngle();
  Point* center = drawable->getCenter().get();
  SDL_RendererFlip flip = drawable->getFlip();
  logSDLError(SDL_RenderCopyEx(this->renderer, textureData, clip, &renderQuad,
                               angle, center, flip),
              "Renderer::prepare()");
}

void Renderer::render() {
  // Renders to the screen everything previously drawn with Renderer::prepare()
  SDL_RenderPresent(this->renderer);
}

void Renderer::clear() { SDL_RenderClear(this->renderer); }

SDL_Texture* Renderer::prepareTexture(TextureSPtr textureSPtr) {
  SDL_Surface* pixelData = textureSPtr->getPixelData();
  // TODO: Color key is static for now, might want to se it
  // in drawingComponent
  SDL_SetColorKey(pixelData, SDL_TRUE,
                  SDL_MapRGB(pixelData->format, 0, 0xFF, 0xFF));
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(this->renderer, pixelData);
  if (texture == nullptr) {
    logSDLError(SDL_ERROR_OCCURRED, "Renderer::prepareTexture");
  }
  return texture;
}
