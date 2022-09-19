#include "Background.hh"

Background::Background(const FilePathSPtr texturePathSPtr,
                       const DrawingCompSPtr drawingCompSPtr,
                       const PositionUnit x, const PositionUnit y) {
  this->positionCompSPtr = PositionCompSPtr(new PositionComp(x, y));

  // TODO: This is a hack just to see if drawing occurs.
  this->drawingCompSPtr = DrawingCompSPtr(new DrawingComp(
      positionCompSPtr, TextureSPtr(new Texture(texturePathSPtr)),
      PointSPtr(new SDL_Point{.x = 55, .y = 55})));
}

DrawingCompSPtr Background::getDrawingCompSPtr() {
  return this->drawingCompSPtr;
}
