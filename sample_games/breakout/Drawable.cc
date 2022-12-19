#include "Drawable.hh"

#include <SDL2/SDL_image.h>

Drawable::Drawable(const Vect2D& center, const int height, const int width, const std::string& texturePath)
    : _center(center), _height(height), _width(width) {
  SDL_Surface* pixelData = IMG_Load(texturePath.c_str());
  SDL_SetColorKey(pixelData, SDL_FALSE, SDL_MapRGB(pixelData->format, 0, 0xFF, 0xFF));
}

Drawable::~Drawable() { SDL_FreeSurface(this->_pixelData); }

Vect2D Drawable::getCenter() const { return this->_center; }
int Drawable::getHeight() const { return this->_height; }
int Drawable::getWidth() const { return this->_width; }
SDL_Surface* Drawable::getPixelData() const { return this->_pixelData; }
