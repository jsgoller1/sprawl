#include "DrawingManager.hh"

#include "DrawingComponent.hh"
#include "GraphicsSettings.hh"
#include "Logging.hh"
#include "Texture.hh"

DrawingManager::DrawingManager(const GraphicsSettings& graphicsSettings)
    : _screenWidth(graphicsSettings.screenWidth),
      _screenHeight(graphicsSettings.screenHeight),
      _useHardwareAcceleration(graphicsSettings.useHardwareAcceleration),
      _useVSync(graphicsSettings.useVSync) {
  // Init SDL, create SDL window, create SDL renderer
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_FATAL_SYS(SDL, "Could not init SDL; {0}", Logging::getSDLError());
    throw;
  }
  this->_window = SDL_CreateWindow("Sprawl Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   int(this->_screenWidth), int(this->_screenHeight), SDL_WINDOW_SHOWN);
  if (this->_window == nullptr) {
    LOG_FATAL_SYS(SDL, "Window could not be created! {0}", Logging::getSDLError());
    throw;
  }

  Uint32 flags = 0;
  flags |= (this->_useHardwareAcceleration ? SDL_RENDERER_ACCELERATED : 0);
  flags |= (this->_useVSync ? SDL_RENDERER_PRESENTVSYNC : 0);
  int windowDriverIndex = -1;
  this->_renderer = (SDL_CreateRenderer(this->_window, windowDriverIndex, flags));
  if (this->_renderer == nullptr) {
    LOG_FATAL_SYS(SDL, "Could not create SDL Renderer. {0}", Logging::getSDLError());
  }
}

DrawingManager::~DrawingManager() {
  SDL_DestroyWindow(this->_window);
  SDL_Quit();
}

DrawingManager::ManagementEntry::ManagementEntry(const std::shared_ptr<PositionComponent> positionComponent,
                                                 const std::shared_ptr<DrawingComponent> drawingComponent)
    : positionComponent(positionComponent), drawingComponent(drawingComponent) {}

void DrawingManager::manage(const std::shared_ptr<Identity> identity,
                            const std::shared_ptr<PositionComponent> positionComponent,
                            const std::shared_ptr<DrawingComponent> drawingComponent) {
  if (this->managementEntries.find(identity) != this->managementEntries.end()) {
    // TODO: Log a warning
    return;
  }
  std::shared_ptr<ManagementEntry> entry =
      std::shared_ptr<ManagementEntry>(new ManagementEntry(positionComponent, drawingComponent));
  this->managementEntries.insert(
      std::pair<std::shared_ptr<Identity>, std::shared_ptr<ManagementEntry>>(identity, entry));
}

void DrawingManager::unmanage(const std::shared_ptr<Identity> identity) {
  if (this->managementEntries.find(identity) == this->managementEntries.end()) {
    // TODO: Log a warning
    return;
  }
  this->managementEntries.erase(identity);
}
void DrawingManager::gameLoopUpdate(const time_ms duration) {
  // TODO: Duration parameter exists for the sake of API consistency
  // even though we don't need it yet; we will use it for animation (probably)
  (void)duration;

  this->clear();
  std::shared_ptr<Identity> identity;
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;
  for (std::pair<std::shared_ptr<Identity>, std::shared_ptr<ManagementEntry>> mapping : this->managementEntries) {
    identity = mapping.first;
    positionComponent = mapping.second->positionComponent;
    drawingComponent = mapping.second->drawingComponent;
    this->prepare(*positionComponent, *drawingComponent);
  }
  SDL_RenderPresent(this->_renderer);
}

void DrawingManager::prepare(const PositionComponent& positionComponent, const DrawingComponent& drawable) const {
  /* Takes a DrawingComponent and prepares it off-screen for rendering.*/
  Vect2D drawPoint = this->toScreenCoordinates(this->getDrawPoint(positionComponent));

  SDL_Rect renderQuad = {// TODO: Do we really just want to cast to int?
                         int(drawPoint.x()), int(drawPoint.y()), int(drawable.getWidth()), int(drawable.getHeight())};
  SDL_Texture* textureData = (drawable.getTexture()) ? this->prepareTexture(*drawable.getTexture()) : nullptr;
  SDL_Rect* clip = nullptr;
  Angle angle = drawable.getAngle();
  SDL_RendererFlip flip = drawable.getFlip();
  SDL_Point center = SDL_Point{.x = int(positionComponent.x()), .y = int(positionComponent.y())};

  if (SDL_RenderCopyEx(this->_renderer, textureData, clip, &renderQuad, angle, &center, flip)) {
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

void DrawingManager::clear() const { SDL_RenderClear(this->_renderer); }

SDL_Texture* DrawingManager::prepareTexture(const Texture& texture) const {
  SDL_Surface* pixelData = texture.getPixelData();
  // TODO: Color key is static for now, might want to se it
  // in drawingComponentonent
  SDL_SetColorKey(pixelData, SDL_FALSE, SDL_MapRGB(pixelData->format, 0, 0xFF, 0xFF));
  SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(this->_renderer, pixelData);
  return sdlTexture;
}

Vect2D DrawingManager::getDrawPoint(const PositionComponent& positionComponent) const {
  // Get the specific point SDL should use for drawing; SDL treats
  // this as the top left of the image and draws from there. We do not
  // need to account for other SDL specifics here (i.e. y-axis flip or top left
  // corner.)

  return positionComponent.getTopLeft();
}

Vect2D DrawingManager::toScreenCoordinates(const Vect2D& vect) const {
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
