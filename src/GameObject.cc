#include "GameObject.hh"

GameObject::GameObject(const PointSPtr center, const GameObjectNameSPtr name,
                       const PhysicsCompSPtr physicsComp,
                       const FilePathSPtr texturePath,
                       const DrawingCompSPtr drawingComp) {
  this->positionComp = PositionCompSPtr(new PositionComp(center));
  this->name = name;
  this->physicsComp = (physicsComp == nullptr)
                          ? PhysicsCompSPtr(new PhysicsComp())
                          : physicsComp;
  this->drawingComp = (drawingComp == nullptr)
                          ? DrawingCompSPtr(new DrawingComp())
                          : drawingComp;
  if (texturePath != nullptr) {
    this->drawingComp->setTexture(TextureSPtr(new Texture(texturePath)));
  }
}

DrawingCompSPtr GameObject::getDrawingCompSPtr() { return this->drawingComp; }
