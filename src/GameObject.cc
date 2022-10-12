#include "GameObject.hh"
GameObject::GameObject(
    const shared_ptr<EntityName> entityName,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<CollisionDetectionComponent> collisionDetectionComponent,
    const shared_ptr<PhysicsComponent> physicsComponent,
    const shared_ptr<DrawingComponent> drawingComponent)
    : Entity(entityName) {
  this->positionComponent =
      (positionComponent == nullptr)
          ? shared_ptr<PositionComponent>(new PositionComponent(0.0, 0.0))
          : positionComponent;

  this->collisionDetectionComponent =
      (collisionDetectionComponent == nullptr)
          ? shared_ptr<CollisionDetectionComponent>(
                new CollisionDetectionComponent(this->positionComponent))
          : collisionDetectionComponent;

  this->physicsComponent =
      (physicsComponent == nullptr)
          ? shared_ptr<PhysicsComponent>(
                new PhysicsComponent(this->identity, this->positionComponent,
                                     this->collisionDetectionComponent))
          : physicsComponent;

  this->drawingComponent = (drawingComponent == nullptr)
                               ? shared_ptr<DrawingComponent>(
                                     new DrawingComponent(positionComponent))
                               : drawingComponent;
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
