#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Memory.hh"
#include "PositionComp.hh"
#include "Types.hh"

class Texture {
 public:
  Texture(const FilePathSPtr path);
  ~Texture();
  void render();
  void setColor();
  void setAlpha();
  void setBlend();
  PositionUnit getHeight();
  PositionUnit getWidth();
  SDL_Surface* getPixelData();

 private:
  SDL_Surface* pixelData;
  FilePathSPtr path;
  PositionUnit height;
  PositionUnit width;
};

typedef shared_ptr<Texture> TextureSPtr;
