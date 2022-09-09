#include "Screen.hh"

#include "Logger.hh"

Screen::Screen() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    string message = "SDL could not initialize! SDL_Error: ";
    message += string((char*)SDL_GetError());
    gLogger.log(message);
    throw;
  }
  this->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (this->window == nullptr) {
    string message = "Window could not be created! SDL_Error: ";
    message += string((char*)SDL_GetError());
    gLogger.log(message);
    throw;
  }
}

Screen::~Screen() {
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

void Screen::draw() {
  this->surface.reset(SDL_GetWindowSurface(this->window));
  // TODO: Get all objects in the world that are ready to be drawn
  SDL_UpdateWindowSurface(this->window);
}
