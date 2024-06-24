#include "GraphicsManager3D.hh"

GraphicsManager3D::~GraphicsManager3D() {}

void GraphicsManager3D::initialize(const GraphicsSettings& graphicsSettings) {
  (void)graphicsSettings;
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return;
  }

  this->_screenWidth = 1600;
  this->_screenHeight = 1200;

  // Init SDL, create SDL window, create SDL renderer
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_FATAL_SYS(SDL, "Could not init SDL; {0}", Logging::getSDLError());
    throw;
  }
  this->_window = SDL_CreateWindow("Sprawl Engine (3D)", int(this->_screenWidth), int(this->_screenHeight), 0);
  if (this->_window == nullptr) {
    LOG_FATAL_SYS(SDL, "Window could not be created! {0}", Logging::getSDLError());
    throw;
  }
}

void GraphicsManager3D::gameLoopUpdate(const time_ms duration) { (void)duration; }
