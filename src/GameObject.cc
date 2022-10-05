#include "GameObject.hh"

void GameObject::init(
    const shared_ptr<Vect2D> center, const GameObjectNameSPtr name,
    const shared_ptr<PhysicsComponent> physicsComp,
    const DrawingCompSPtr drawingComp, const FilePathSPtr texturePath,
    const shared_ptr<CollisionDetectionComponent> collisionDetectionComponent,
    const shared_ptr<BoundingBoxParams> boundingBoxParams) {
  this->name = name;
  this->positionComp = shared_ptr<PositionComp>(new PositionComp(center));

  if (collisionDetectionComponent != nullptr) {
    this->collisionDetectionComponent = collisionDetectionComponent;
  } else {
    if (boundingBoxParams != nullptr) {
      this->collisionDetectionComponent =
          shared_ptr<CollisionDetectionComponent>(
              new CollisionDetectionComponent(positionComp, boundingBoxParams));
    } else {
      log(string("Warning: GameObject initialized without injected "
                 "CollisionDetectionComponent or BoundingBoxParams: ") +
          *name);
    }
  }

  this->physicsComp = (physicsComp == nullptr)
                          ? shared_ptr<PhysicsComponent>(new PhysicsComponent(
                                this->name, this->positionComp,
                                this->collisionDetectionComponent))
                          : physicsComp;
  this->drawingComp = (drawingComp == nullptr)
                          ? DrawingCompSPtr(new DrawingComp(this->positionComp))
                          : drawingComp;

  if (texturePath != nullptr) {
    this->drawingComp->setTexture(TextureSPtr(new Texture(texturePath)));
  }
}

DrawingCompSPtr GameObject::getDrawingComponent() { return this->drawingComp; }
