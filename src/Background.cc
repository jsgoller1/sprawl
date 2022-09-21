#include "Background.hh"

Background::Background(const FilePathSPtr texturePathSPtr,
                       DrawingCompSPtr drawingCompSPtr, const PositionUnit x,
                       const PositionUnit y) {
  this->positionCompSPtr = PositionCompSPtr(new PositionComp(x, y));

  if (drawingCompSPtr == nullptr) {
    drawingCompSPtr = DrawingCompSPtr(new DrawingComp(
        this->positionCompSPtr, TextureSPtr(new Texture(texturePathSPtr))));
  }
  this->drawingCompSPtr = drawingCompSPtr;

  // TODO: This is ugly and stupid; initial position should be treated
  // universally as a center point and handled more cleanly. Use given x/y
  // coordinates as the texture's center, not the upper left corner
  /*
  this->positionCompSPtr->setX(this->positionCompSPtr->getX() -
                               (this->drawingCompSPtr->getWidth() / 2));
  this->positionCompSPtr->setY(this->positionCompSPtr->getY() -
                               (this->drawingCompSPtr->getHeight() / 2));
  */
}

DrawingCompSPtr Background::getDrawingCompSPtr() {
  return this->drawingCompSPtr;
}
