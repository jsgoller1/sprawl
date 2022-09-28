#include "GameObject.hh"

void GameObject::init(const shared_ptr<Vect2D> center,
                      const GameObjectNameSPtr name,
                      const shared_ptr<PhysicsComponent> physicsComp,
                      const FilePathSPtr texturePath,
                      const DrawingCompSPtr drawingComp) {
  this->positionComp = shared_ptr<PositionComp>(new PositionComp(center));
  this->name = name;
  this->physicsComp = (physicsComp == nullptr)
                          ? shared_ptr<PhysicsComponent>(
                                new PhysicsComponent(this->positionComp))
                          : physicsComp;
  this->drawingComp = (drawingComp == nullptr)
                          ? DrawingCompSPtr(new DrawingComp(this->positionComp))
                          : drawingComp;
  if (texturePath != nullptr) {
    this->drawingComp->setTexture(TextureSPtr(new Texture(texturePath)));
  }
}
GameObject::GameObject(const shared_ptr<Vect2D> center,
                       const GameObjectNameSPtr name,
                       const shared_ptr<PhysicsComponent> physicsComp,
                       const FilePathSPtr texturePath,
                       const DrawingCompSPtr drawingComp) {
  this->init(center, name, physicsComp, texturePath, drawingComp);
}

GameObject::GameObject(const shared_ptr<Vect2D> center,
                       const GameObjectNameSPtr name,
                       const FilePathSPtr texturePath,
                       const DrawingCompSPtr drawingComp) {
  shared_ptr<PhysicsComponent> physicsComp = nullptr;
  this->init(center, name, physicsComp, texturePath, drawingComp);
}

DrawingCompSPtr GameObject::getDrawingComponent() { return this->drawingComp; }
shared_ptr<PhysicsComponent> GameObject::getPhysicsComponent() {
  return this->physicsComp;
}

void GameObject::inferBoundingBoxFromTexture() {
  shared_ptr<Texture> texture = this->drawingComp->getTexture();
  this->physicsComp->setBoundingBox(texture->getHeight(), texture->getWidth());
}
