#include "Screen.hh"

Screen::Screen(const ScreenWidth width, const ScreenHeight height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    string message = "SDL could not initialize! SDL_Error: ";
    message += string((char*)SDL_GetError());
    log(message);
    throw;
  }
  this->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, width, height,
                                  SDL_WINDOW_SHOWN);
  if (this->window == nullptr) {
    string message = "Window could not be created! SDL_Error: ";
    message += string((char*)SDL_GetError());
    log(message);
    throw;
  }

  bool useHardwareAccel = true;
  bool useVSync = true;
  this->renderer = shared_ptr<Renderer>(
      new Renderer(this->window, useHardwareAccel, useVSync));
}

Screen::~Screen() {
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void Screen::drawAll(
    const shared_ptr<vector<shared_ptr<DrawingComponent>>> drawables) const {
  this->clear();
  for (auto drawable : *(drawables.get())) {
    this->renderer->prepare(drawable);
  }
  renderer->render();
}

void Screen::update() const { this->renderer->render(); }

void Screen::clear() const { this->renderer->clear(); }
