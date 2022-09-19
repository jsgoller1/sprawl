#include "Character.hh"

Character::Character(const CharacterNameSPtr name,
                     const FilePathSPtr texturePath, const PointSPtr center) {
  this->name = name;
  this->positionComp = PositionCompSPtr(new PositionComp(center));

  TextureSPtr texture = TextureSPtr(new Texture(texturePath));
  this->drawingCompSPtr =
      DrawingCompSPtr(new DrawingComp(this->positionComp, texture));
}
