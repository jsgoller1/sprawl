#pragma once

#include "SDL2/SDL.h"

#include "PositionComponent.hh"
#include "Types.hh"

class Texture {
 public:
  Texture(const FilePath& path);
  Texture(const std::shared_ptr<FilePath> path);

  ~Texture();

  // PixelData, Height, and Width are all dependent on
  // the image data loaded from disk, so if they're going to be modified,
  // it should be by loading a new texture (presently; eventually, we'll allow
  // for stuff like color masking and whatnot)
  SDL_Surface* getPixelData() const;
  PositionUnit getHeight() const;
  PositionUnit getWidth() const;

  void render();

 private:
  SDL_Surface* pixelData;
  FilePath path;
  PositionUnit height;
  PositionUnit width;
};
