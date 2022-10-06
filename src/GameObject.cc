#include "GameObject.hh"

GameObject::GameObject(const EntityName& entityName, const shared_ptr<PositionComponent> positionComponent,
                       const shared_ptr<CollisionComponent> collisionComponent,
                       const shared_ptr<PhysicsComponent> physicsComponent,
                       const shared_ptr<DrawingComponent> drawingComponent)
    : Entity(entityName) {
  this->positionComponent = (positionComponent == nullptr)
                                ? shared_ptr<PositionComponent>(new PositionComponent(this->getIdentity(), 0.0, 0.0))
                                : positionComponent;

  this->collisionComponent =
      (collisionComponent == nullptr)
          ? shared_ptr<CollisionComponent>(new CollisionComponent(this->getIdentity(), this->positionComponent))
          : collisionComponent;

  this->physicsComponent = (physicsComponent == nullptr)
                               ? shared_ptr<PhysicsComponent>(new PhysicsComponent(this->getIdentity()))
                               : physicsComponent;

  this->drawingComponent =
      (drawingComponent == nullptr)
          ? shared_ptr<DrawingComponent>(new DrawingComponent(this->getIdentity(), this->positionComponent))
          : drawingComponent;
}

GameObject::~GameObject() {}

void GameObject::inferBoundingBoxFromTexture() {
  shared_ptr<Texture> texture = this->drawingComponent->getTexture();
  this->collisionComponent->height(texture->getHeight());
  this->collisionComponent->width(texture->getWidth());
}

// Private
void GameObject::setPhysicsComponent_impl(PhysicsComponent* const comp) { this->physicsComponent = comp->getptr(); }
PhysicsComponent* GameObject::getPhysicsComponent_impl() const { return this->physicsComponent.get(); }
