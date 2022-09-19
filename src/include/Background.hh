#pragma once

#include "DrawingComp.hh"
#include "PositionComp.hh"
#include "Screen.hh"
#include "Texture.hh"
#include "Types.hh"

class Background {
 public:
  Background(const FilePathSPtr texturePathSPtr,
             DrawingCompSPtr drawingCompSPtr = nullptr,
             const PositionUnit x = 0, const PositionUnit y = 0);

  DrawingCompSPtr getDrawingCompSPtr();

 private:
  PositionCompSPtr positionCompSPtr;
  DrawingCompSPtr drawingCompSPtr;
};

typedef shared_ptr<Background> BackgroundSPtr;
