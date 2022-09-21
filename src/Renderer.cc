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

  PointSPtr drawPoint = drawable->getDrawPoint();
  SDL_Rect renderQuad = {drawPoint->x, drawPoint->y, drawable->getWidth(),
                         drawable->getHeight()};
  SDL_Texture* textureData = this->prepareTexture(drawable->getTexture());
  SDL_Rect* clip = nullptr;
  Angle angle = drawable->getAngle();
  SDL_RendererFlip flip = drawable->getFlip();
  SDL_Point center = SDL_Point{.x = drawable->getX(), .y = drawable->getY()};

  logSDLError(SDL_RenderCopyEx(this->renderer, textureData, clip, &renderQuad,
                               angle, &center, flip),
              "Renderer::prepare()");

  // TODO: A memory leak that crashed my crashed my machine repeatedly by
  // allocating ~1GB/sec occurred because I forgot this destroy call. Would
  // be useful to set up textures with smart pointers that call
  // SDL_DestroyTexture when cleaned up.
  SDL_DestroyTexture(textureData);
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
  SDL_SetColorKey(pixelData, SDL_FALSE,
                  SDL_MapRGB(pixelData->format, 0, 0xFF, 0xFF));
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(this->renderer, pixelData);
  if (texture == nullptr) {
    logSDLError(SDL_ERROR_OCCURRED, "Renderer::prepareTexture");
  }
  return texture;
}
