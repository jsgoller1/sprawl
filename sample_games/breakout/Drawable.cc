#include "Drawable.hh"

#include <SDL2/SDL_image.h>

Drawable::Drawable(const Vect2D& center, const int width, const int height, const std::string& texturePath)
    : _center(center), _height(height), _width(width) {
  this->_pixelData = IMG_Load(texturePath.c_str());
  SDL_SetColorKey(this->_pixelData, SDL_TRUE, SDL_MapRGB(this->_pixelData->format, 0xff, 0xff, 0xff));
}

Drawable::~Drawable() { SDL_FreeSurface(this->_pixelData); }

Vect2D Drawable::getCenter() const { return this->_center; }
void Drawable::setCenter(const Vect2D& center) { this->_center = center; }
int Drawable::getHeight() const { return this->_height; }
int Drawable::getWidth() const { return this->_width; }
SDL_Surface* Drawable::getPixelData() const { return this->_pixelData; }
