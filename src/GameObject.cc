#include "GameObject.hh"
GameObject::GameObject(
    const shared_ptr<EntityName> entityName,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<CollisionDetectionComponent> collisionDetectionComponent,
    const shared_ptr<PhysicsComponent> physicsComponent,
    const shared_ptr<DrawingComponent> drawingComponent)
    : positionComponent(positionComponent),
      physicsComponent(physicsComponent),
      collisionDetectionComponent(collisionDetectionComponent),
      drawingComponent(drawingComponent),
      Entity(entityName) {
  if (this->positionComponent == nullptr) {
    this->positionComponent =
        shared_ptr<PositionComponent>(new PositionComponent(0.0, 0.0));
  }
  if (this->collisionDetectionComponent == nullptr) {
    this->collisionDetectionComponent = shared_ptr<CollisionDetectionComponent>(
        new CollisionDetectionComponent(this->positionComponent));
  }
  if (this->physicsComponent == nullptr) {
    this->physicsComponent = shared_ptr<PhysicsComponent>(
        new PhysicsComponent(this->identity, this->positionComponent,
                             this->collisionDetectionComponent));
  }
  if (this->drawingComponent == nullptr) {
  }
}

void GameObject::inferBoundingBoxFromTexture() {
  shared_ptr<Texture> texture = this->drawingComponent->getTexture();
  this->collisionDetectionComponent->setBoundingBoxParams(
      shared_ptr<BoundingBoxParams>(
          new BoundingBoxParams(texture->getHeight(), texture->getWidth())));
}

// Private
void GameObject::setPhysicsComponent_impl(PhysicsComponent* const comp) {
  this->physicsComponent = comp->getptr();
}
PhysicsComponent* GameObject::getPhysicsComponent_impl() const {
  return this->physicsComponent.get();
}
