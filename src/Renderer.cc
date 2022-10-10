#include "Renderer.hh"

Renderer::Renderer(SDL_Window* const window, const bool useHardwareAcceleration,
                   const bool useVSync) {
  Uint32 flags = 0;
  flags |= (useHardwareAcceleration ? SDL_RENDERER_ACCELERATED : 0);
  flags |= (useVSync ? SDL_RENDERER_PRESENTVSYNC : 0);
  int windowDriverIndex = -1;
  this->renderer = (SDL_CreateRenderer(window, windowDriverIndex, flags));
  if (this->renderer == nullptr) {
    logSDLError(SDL_ERROR_OCCURRED, "Renderer::Renderer()");
  }
}

void Renderer::prepare(const shared_ptr<DrawingComponent> drawable) const {
  /* Takes a DrawingComponent and prepares it off-screen for rendering.
   */

  shared_ptr<Vect2D> drawPoint = drawable->getDrawPoint();
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

void Renderer::render() const {
  // Renders to the screen everything previously drawn with Renderer::prepare()
  SDL_RenderPresent(this->renderer);
}

void Renderer::clear() const { SDL_RenderClear(this->renderer); }

SDL_Texture* Renderer::prepareTexture(const shared_ptr<Texture> texture) const {
  SDL_Surface* pixelData = texture->getPixelData();
  // TODO: Color key is static for now, might want to se it
  // in drawingComponentonent
  SDL_SetColorKey(pixelData, SDL_FALSE,
                  SDL_MapRGB(pixelData->format, 0, 0xFF, 0xFF));
  SDL_Texture* sdlTexture =
      SDL_CreateTextureFromSurface(this->renderer, pixelData);
  if (texture == nullptr) {
    logSDLError(SDL_ERROR_OCCURRED, "Renderer::prepareTexture");
  }
  return sdlTexture;
}
