#pragma once

#include <SDL2/SDL.h>

#include "Memory.hh"
#include "Types.hh"

class Texture {
 public:
  Texture(const FilePathSPtr path) : path(path){};
  Texture(const FilePath path) {
    this->path = FilePathSPtr(new FilePath(path));
  }
  void load(const FilePathSPtr path);
  void render();
  void setColor();
  void setAlpha();
  void setBlend();
  void getHeight();
  void getWidth();
  shared_ptr<SDL_Texture> getRawData();

 private:
  shared_ptr<SDL_Texture> texture;
  FilePathSPtr path;
};

typedef shared_ptr<Texture> TextureSPtr;
