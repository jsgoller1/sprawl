#include "IDrawing.hh"

#include <SDL2/SDL_image.h>

IDrawing::IDrawing(const Vect2D& center, const int width, const int height, const std::string& texturePath,
                   const std::shared_ptr<DrawingProxy> drawingProxy)
    : _drawingProxy(drawingProxy), _center(center), _height(height), _width(width) {
  this->_pixelData = IMG_Load(texturePath.c_str());
  SDL_SetColorKey(this->_pixelData, SDL_TRUE, SDL_MapRGB(this->_pixelData->format, 0xff, 0xff, 0xff));
}
IDrawing::~IDrawing() { SDL_FreeSurface(this->_pixelData); }
int IDrawing::getHeight() const { return this->_height; }
int IDrawing::getWidth() const { return this->_width; }
Vect2D IDrawing::getCenter() const { return this->_center; }
void IDrawing::setCenter(const Vect2D& center) { this->_center = center; }
void IDrawing::updateCenter(const Vect2D& delta) {
  this->_center.x += delta.x;
  this->_center.y += delta.y;
}
Vect2D IDrawing::getTopLeft() const {
  Vect2D topLeft = this->_center;
  topLeft.x -= this->_width / 2;
  topLeft.y += this->_height / 2;
  return topLeft;
}
// SDL_Surface* IDrawing::getPixelData() const { return this->_pixelData; }
void IDrawing::draw() const { this->_drawingProxy->draw(this->_center, this->_width, this->_height, this->_pixelData); }
