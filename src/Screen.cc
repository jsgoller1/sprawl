#include "Screen.hh"

#include <vector>

Screen::Screen(const ScreenWidth width, const ScreenHeight height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_FATAL_SYS(SDL, "Could not init SDL; {0}", Logging::getSDLError());
    throw;
  }
  this->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, int(width),
                                  int(height), SDL_WINDOW_SHOWN);
  if (this->window == nullptr) {
    LOG_FATAL_SYS(SDL, "Window could not be created! {0}", Logging::getSDLError());
    throw;
  }

  bool useHardwareAccel = true;
  bool useVSync = true;
  this->_height = height;
  this->_width = width;
  this->renderer = std::shared_ptr<Renderer>(new Renderer(width, height, this->window, useHardwareAccel, useVSync));
}

Screen::~Screen() {
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void Screen::drawAll(const std::shared_ptr<std::vector<std::shared_ptr<DrawingComponent>>> drawables) const {
  this->clear();
  for (auto drawable : *(drawables.get())) {
    this->renderer->prepare(drawable);
  }
  renderer->render();
}

void Screen::update() const { this->renderer->render(); }

void Screen::clear() const { this->renderer->clear(); }
