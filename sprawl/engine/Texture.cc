#include "Texture.hh"

#include <SDL2/SDL_image.h>

Texture::Texture(const std::shared_ptr<FilePath> path) : Texture(*path) {}

Texture::Texture(const FilePath& path) {
  this->path = path;
  this->pixelData = IMG_Load(this->path.c_str());
  if (this->pixelData == nullptr) {
    LOG_ERROR("Failed to load texture at {0}. SDL error: {1}", path, Logging::getSDLError());
    return;
  }
  this->height = this->pixelData->h;
  this->width = this->pixelData->w;
};

Texture::~Texture() { SDL_FreeSurface(this->pixelData); }

SDL_Surface* Texture::getPixelData() const { return this->pixelData; }
PositionUnit Texture::getHeight() const { return this->height; }
PositionUnit Texture::getWidth() const { return this->width; }
