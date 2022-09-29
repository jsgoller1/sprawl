#include "Texture.hh"

Texture::Texture(const FilePathSPtr path) {
  this->path = path;
  this->pixelData = IMG_Load(this->path.get()->c_str());
  // TODO: Catch exception if image loading fails.
  this->height = this->pixelData->h;
  this->width = this->pixelData->w;
};

Texture::~Texture() { SDL_FreeSurface(this->pixelData); }

SDL_Surface* Texture::getPixelData() { return this->pixelData; }
PositionUnit Texture::getHeight() { return this->height; }
PositionUnit Texture::getWidth() { return this->width; }
