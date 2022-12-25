#include "Screen.hh"

#include <iostream>

#include "Vect2D.hh"

Screen::Screen(const int width, const int height) : _width(width), _height(height) {
  // Init SDL, create SDL window, create SDL renderer
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw;
  }

  this->_window = SDL_CreateWindow("Berzerk", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->_width,
                                   this->_height, SDL_WINDOW_SHOWN);
  if (this->_window == nullptr) {
    throw;
  }

  Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  int windowDriverIndex = -1;
  this->_renderer = (SDL_CreateRenderer(this->_window, windowDriverIndex, flags));
  if (this->_renderer == nullptr) {
    throw;
  }
}

Screen::~Screen() {
  SDL_DestroyWindow(this->_window);
  SDL_Quit();
}

void Screen::prepare(const Vect2D& center, const int height, const int width, SDL_Surface* pixelData) {
  Vect2D drawPoint = this->toScreenCoordinates(this->getDrawPoint(center, height, width));

  SDL_Rect renderQuad = {drawPoint.x, drawPoint.y, width, height};
  SDL_Rect* clip = nullptr;
  double angle = 0.0;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_Point sdlCenter = SDL_Point{.x = drawPoint.x, .y = drawPoint.y};
  SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, pixelData);
  if (SDL_RenderCopyEx(this->_renderer, texture, clip, &renderQuad, angle, &sdlCenter, flip)) {
    std::cout << "Couldn't draw texture" << std::endl;
    this->printSDLError();
  }
  SDL_DestroyTexture(texture);
}

void Screen::draw() { SDL_RenderPresent(this->_renderer); }

void Screen::clear() { SDL_RenderClear(this->_renderer); }

int Screen::getHeight() const { return this->_height; }
int Screen::getWidth() const { return this->_width; }

Vect2D Screen::getTopLeft() const { return Vect2D{0, 0}; }
Vect2D Screen::getTopRight() const { return Vect2D{this->_width, 0}; }
Vect2D Screen::getBottomLeft() const { return Vect2D{0, this->_height}; }
Vect2D Screen::getBottomRight() const {
  return Vect2D{
      this->_width,
      this->_height,
  };
}

Vect2D Screen::getDrawPoint(const Vect2D& center, const int height, const int width) const {
  // Get the specific point SDL should use for drawing; SDL treats
  // this as the top left of the image and draws from there. We do not
  // need to account for other SDL specifics here (i.e. y-axis flip or top left
  // corner.)

  return Vect2D(center.x - width / 2, center.y + height / 2);
}

Vect2D Screen::toScreenCoordinates(const Vect2D& vect) const {
  /*
   * SDL: (0,0) is the upper left of the display, (ScreenWidth, ScreenHeight) is
   * the bottom right. (100,100) is beneath (100,0)
   * Game world: (0,0) is the center of the screen. (100,100) is above (100,0).
   * To translate from game world to SDL, invert the Y coordinates, and move
   * everything by (ScreenWidth/2, ScreenHeight/2).
   */

  Vect2D screenCoords = Vect2D(vect);
  screenCoords.y = screenCoords.y - (this->_height / 2);
  screenCoords.x = screenCoords.x + (this->_width / 2);
  screenCoords.y = screenCoords.y * -1;
  return screenCoords;
}

Vect2D Screen::toWorldCoordinates(const Vect2D& vect) const {
  Vect2D worldCoords = Vect2D(vect);
  worldCoords.y = worldCoords.y * -1;
  worldCoords.x = worldCoords.x - (this->_width / 2);
  worldCoords.y = worldCoords.y + (this->_height / 2);
  return worldCoords;
}

void Screen::printSDLError() {
  std::string error = std::string(SDL_GetError());
  std::cout << "SDL Error message: " << error << std::endl;
  SDL_ClearError();
}
