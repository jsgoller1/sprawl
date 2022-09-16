#include "Background.hh"

#include "Texture.hh"

Background::Background(const FilePathSPtr texturePathSPtr, const PositionUnit x,
                       const PositionUnit y) {
  this->textureSPtr = TextureSPtr(new Texture(texturePathSPtr));
  this->positionCompSPtr = PositionCompSPtr(new PositionComp(x, y));
}
