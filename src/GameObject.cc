#include "GameObject.hh"

GameObject::GameObject(const shared_ptr<Vect2D> center,
                       const GameObjectNameSPtr name,
                       const shared_ptr<PhysicsComp> physicsComp,
                       const FilePathSPtr texturePath,
                       const DrawingCompSPtr drawingComp) {
  this->positionComp = shared_ptr<PositionComp>(new PositionComp(center));
  this->name = name;
  this->physicsComp =
      (physicsComp == nullptr)
          ? shared_ptr<PhysicsComp>(new PhysicsComp(this->positionComp))
          : physicsComp;
  this->drawingComp = (drawingComp == nullptr)
                          ? DrawingCompSPtr(new DrawingComp(this->positionComp))
                          : drawingComp;
  if (texturePath != nullptr) {
    this->drawingComp->setTexture(TextureSPtr(new Texture(texturePath)));
  }
}

DrawingCompSPtr GameObject::getDrawingComponent() { return this->drawingComp; }
shared_ptr<PhysicsComp> GameObject::getPhysicsComponent() {
  return this->physicsComp;
}

void GameObject::inferBoundingBoxFromTexture() {
  shared_ptr<Texture> texture = this->drawingComp->getTexture();
  this->physicsComp->setBoundingBox(texture->getHeight(), texture->getWidth());
}
