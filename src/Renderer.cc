#include "Renderer.hh"

Renderer::Renderer(const ScreenWidth screenWidth, const ScreenHeight screenHeight, SDL_Window* const window,
                   const bool useHardwareAcceleration, const bool useVSync) {
  this->_screenWidth = screenWidth;
  this->_screenHeight = screenHeight;

  Uint32 flags = 0;
  flags |= (useHardwareAcceleration ? SDL_RENDERER_ACCELERATED : 0);
  flags |= (useVSync ? SDL_RENDERER_PRESENTVSYNC : 0);
  int windowDriverIndex = -1;
  this->renderer = (SDL_CreateRenderer(window, windowDriverIndex, flags));
  if (this->renderer == nullptr) {
    LOG_FATAL_SYS(SDL, "Could not create SDL Renderer. {0}", Logging::getSDLError());
  }
}

void Renderer::prepare(const shared_ptr<DrawingComponent> drawable) const {
  /* Takes a DrawingComponent and prepares it off-screen for rendering.*/

  Vect2D drawPoint = this->toScreenCoordinates(drawable->getDrawPoint());

  SDL_Rect renderQuad = {// TODO: Do we really just want to cast to int?
                         int(drawPoint.x()), int(drawPoint.y()), int(drawable->getWidth()), int(drawable->getHeight())};
  SDL_Texture* textureData = this->prepareTexture(drawable->getTexture());
  SDL_Rect* clip = nullptr;
  Angle angle = drawable->getAngle();
  SDL_RendererFlip flip = drawable->getFlip();
  SDL_Point center = SDL_Point{.x = int(drawable->getX()), .y = int(drawable->getY())};

  if (SDL_RenderCopyEx(this->renderer, textureData, clip, &renderQuad, angle, &center, flip)) {
    LOG_ERROR_SYS(SDL,
                  "Could not prepare texture: (derive DrawingComponent from  Component to "
                  "get ID) {0}",
                  Logging::getSDLError());
  }

  // TODO: A memory leak that crashed my crashed my machine
  // repeatedly by allocating ~1GB/sec occurred because I forgot
  // this destroy call. Would be useful to set up textures with
  // smart pointers that call SDL_DestroyTexture when cleaned up.
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
  SDL_SetColorKey(pixelData, SDL_FALSE, SDL_MapRGB(pixelData->format, 0, 0xFF, 0xFF));
  SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(this->renderer, pixelData);
  if (texture == nullptr) {
    LOG_ERROR_SYS(SDL, "Could not create texture. {0}", Logging::getSDLError());
  }
  return sdlTexture;
}

Vect2D Renderer::toScreenCoordinates(const Vect2D& vect) const {
  /*
   * SDL: (0,0) is the upper left of the display, (ScreenWidth, ScreenHeight) is
   * the bottom right. (100,100) is beneath (100,0)
   * Game world: (0,0) is the center of the screen. (100,100) is above (100,0).
   * To translate from game world to SDL, invert the Y coordinates, and move
   * everything by (ScreenWidth/2, ScreenHeight/2).
   */

  Vect2D screenCoords = Vect2D(vect);
  screenCoords.y(screenCoords.y() * -1.0);
  screenCoords.x(screenCoords.x() + (this->_screenWidth / 2));
  screenCoords.y(screenCoords.y() + (this->_screenHeight / 2));
  return screenCoords;
}
