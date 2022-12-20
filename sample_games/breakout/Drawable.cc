#include "Drawable.hh"

#include <SDL2/SDL_image.h>

Drawable::Drawable(const Vect2D& center, const int width, const int height, const std::string& texturePath)
    : _center(center), _height(height), _width(width) {
  this->_pixelData = IMG_Load(texturePath.c_str());
  SDL_SetColorKey(this->_pixelData, SDL_TRUE, SDL_MapRGB(this->_pixelData->format, 0xff, 0xff, 0xff));
}
Drawable::~Drawable() { SDL_FreeSurface(this->_pixelData); }
int Drawable::getHeight() const { return this->_height; }
int Drawable::getWidth() const { return this->_width; }
Vect2D Drawable::getCenter() const { return this->_center; }
void Drawable::setCenter(const Vect2D& center) { this->_center = center; }
void Drawable::updateCenter(const Vect2D& delta) {
  this->_center.x += delta.x;
  this->_center.y += delta.y;
}
Vect2D Drawable::getTopLeft() const {
  Vect2D topLeft = this->_center;
  topLeft.x -= this->_width / 2;
  topLeft.y += this->_height / 2;
  return topLeft;
}
Vect2D Drawable::getTopRight() const {
  Vect2D topRight = this->_center;
  topRight.x += this->_width / 2;
  topRight.y += this->_height / 2;
  return topRight;
}
Vect2D Drawable::getBottomLeft() const {
  Vect2D bottomLeft = this->_center;
  bottomLeft.x -= this->_width / 2;
  bottomLeft.y -= this->_height / 2;
  return bottomLeft;
}
Vect2D Drawable::getBottomRight() const {
  Vect2D bottomRight = this->_center;
  bottomRight.x += this->_width / 2;
  bottomRight.y -= this->_height / 2;
  return bottomRight;
}
SDL_Surface* Drawable::getPixelData() const { return this->_pixelData; }
SDL_Rect Drawable::getBoundingBox() const {
  Vect2D topLeft = this->getTopLeft();
  return SDL_Rect{.x = topLeft.x, .y = topLeft.y, .w = this->_width, .h = this->_height};
}
