#include "Texture.hh"

Texture::Texture(const shared_ptr<FilePath> path) {
  this->path = path;
  this->pixelData = IMG_Load(this->path.get()->c_str());
  this->height = this->pixelData->h;
  this->width = this->pixelData->w;
};

Texture::~Texture() { SDL_FreeSurface(this->pixelData); }
