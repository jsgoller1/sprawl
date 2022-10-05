#pragma once

#include "Memory.hh"
#include "PositionComponent.hh"
#include "Types.hh"

class Texture {
 public:
  Texture(const shared_ptr<FilePath> path);
  ~Texture();

  // PixelData, Height, and Width are all dependent on
  // the image data loaded from disk, so if they're going to be modified,
  // it should be by loading a new texture (presently; eventually, we'll allow
  // for stuff like color masking and whatnot)
  SDL_Surface* getPixelData() const { return this->pixelData; }
  PositionUnit getHeight() const { return this->height; }
  PositionUnit getWidth() const { return this->width; }

  void render();

 private:
  SDL_Surface* pixelData;
  shared_ptr<FilePath> path;
  PositionUnit height;
  PositionUnit width;
};
