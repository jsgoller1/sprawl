#pragma once

#include "PositionComp.hh"
#include "Texture.hh"
#include "Types.hh"

class Background {
 public:
  Background(const FilePathSPtr TexturePathSPtr, const PositionUnit x,
             const PositionUnit y);

 private:
  PositionCompSPtr positionCompSPtr;
  TextureSPtr textureSPtr;
};

typedef shared_ptr<Background> BackgroundSPtr;
