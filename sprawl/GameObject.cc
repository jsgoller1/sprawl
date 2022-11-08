#include "GameObject.hh"

GameObject::GameObject(const EntityName& entityName, const std::shared_ptr<PositionComponent> positionComponent,
                       const std::shared_ptr<CollisionComponent> collisionComponent,
                       const std::shared_ptr<PhysicsComponent> physicsComponent,
                       const std::shared_ptr<DrawingComponent> drawingComponent)
    : Entity(entityName) {
  this->positionComponent =
      (positionComponent == nullptr)
          ? std::shared_ptr<PositionComponent>(new PositionComponent(this->getIdentity(), 0.0, 0.0))
          : positionComponent;

  this->collisionComponent =
      (collisionComponent == nullptr)
          ? std::shared_ptr<CollisionComponent>(new CollisionComponent(this->getIdentity(), this->positionComponent))
          : collisionComponent;

  this->physicsComponent = (physicsComponent == nullptr)
                               ? std::shared_ptr<PhysicsComponent>(new PhysicsComponent(this->getIdentity()))
                               : physicsComponent;

  this->drawingComponent =
      (drawingComponent == nullptr)
          ? std::shared_ptr<DrawingComponent>(new DrawingComponent(this->getIdentity(), this->positionComponent))
          : drawingComponent;
}

GameObject::~GameObject() {}

void GameObject::inferBoundingBoxFromTexture() {
  std::shared_ptr<Texture> texture = this->drawingComponent->getTexture();
  this->collisionComponent->height(texture->getHeight());
  this->collisionComponent->width(texture->getWidth());
}

// Private
void GameObject::setPhysicsComponent_impl(PhysicsComponent* const comp) { this->physicsComponent = comp->getptr(); }
PhysicsComponent* GameObject::getPhysicsComponent_impl() const { return this->physicsComponent.get(); }
