#include "Texture.hh"
Texture::Texture(const shared_ptr<FilePath> path) : Texture(*path) {}

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
