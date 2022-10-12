#include "GameObject.hh"
GameObject::GameObject(const shared_ptr<EntityName> entityName,
                       const shared_ptr<PositionComponent> positionComponent,
                       const shared_ptr<CollisionComponent> collisionComponent,
                       const shared_ptr<PhysicsComponent> physicsComponent,
                       const shared_ptr<DrawingComponent> drawingComponent)
    : Entity(entityName) {
  this->positionComponent =
      (positionComponent == nullptr)
          ? shared_ptr<PositionComponent>(new PositionComponent(0.0, 0.0))
          : positionComponent;

  this->collisionComponent =
      (collisionComponent == nullptr)
          ? shared_ptr<CollisionComponent>(
                new CollisionComponent(this->positionComponent))
          : collisionComponent;

  this->physicsComponent =
      (physicsComponent == nullptr)
          ? shared_ptr<PhysicsComponent>(new PhysicsComponent(
                this->getIdentity(), this->positionComponent,
                this->collisionComponent))
          : physicsComponent;

  this->drawingComponent =
      (drawingComponent == nullptr)
          ? shared_ptr<DrawingComponent>(
                new DrawingComponent(this->positionComponent))
          : drawingComponent;
}

void GameObject::inferBoundingBoxFromTexture() {
  shared_ptr<Texture> texture = this->drawingComponent->getTexture();
  this->collisionComponent->setBoundingBoxParams(shared_ptr<BoundingBoxParams>(
      new BoundingBoxParams(texture->getHeight(), texture->getWidth())));
}

// Private
void GameObject::setPhysicsComponent_impl(PhysicsComponent* const comp) {
  this->physicsComponent = comp->getptr();
}
PhysicsComponent* GameObject::getPhysicsComponent_impl() const {
  return this->physicsComponent.get();
}
