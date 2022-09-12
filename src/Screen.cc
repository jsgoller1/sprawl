#include "Screen.hh"

#include "DrawingComponent.hh"
#include "Logger.hh"

Screen::Screen(const ScreenWidth width, const ScreenHeight height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    string message = "SDL could not initialize! SDL_Error: ";
    message += string((char*)SDL_GetError());
    gLogger.log(message);
    throw;
  }
  this->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, width, height,
                                  SDL_WINDOW_SHOWN);
  if (this->window == nullptr) {
    string message = "Window could not be created! SDL_Error: ";
    message += string((char*)SDL_GetError());
    gLogger.log(message);
    throw;
  }

  bool useHardwareAccel = true;
  bool useVSync = true;
  this->renderer =
      RendererSPtr(new Renderer(this->window, useHardwareAccel, useVSync));
}

Screen::~Screen() {
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void Screen::draw(DrawingComponentSPtr drawable) {
  this->renderer->prepare(drawable);
}

void Screen::drawAll(shared_ptr<DrawingComponentSPtrCollection> drawables) {
  this->clear();
  for (DrawingComponentSPtr drawable : *(drawables.get())) {
    this->draw(drawable);
  }
}

void Screen::update() { this->renderer->render(); }

void Screen::clear() {
  // this->surface.reset(SDL_GetWindowSurface(this->window));
}
