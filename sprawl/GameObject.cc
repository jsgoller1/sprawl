#include "GameObject.hh"

#include "BoundingBox.hh"
#include "CollisionComponent.hh"
#include "DrawingComponent.hh"
#include "Identity.hh"
#include "PositionComponent.hh"
#include "SimplePhysicsComponent.hh"

GameObject::GameObject(const EntityName& entityName, const std::shared_ptr<PositionComponent> positionComponent,
                       const std::shared_ptr<CollisionComponent> collisionComponent,
                       const std::shared_ptr<PhysicsComponent> physicsComponent,
                       const std::shared_ptr<DrawingComponent> drawingComponent)
    : Entity(entityName) {
  std::shared_ptr<Identity> id = this->getIdentity().shared_from_this();

  this->drawingComponent = (drawingComponent == nullptr) ? std::make_shared<DrawingComponent>(id) : drawingComponent;
  this->drawingComponent->setOwnerIdentity(id);

  if (positionComponent == nullptr) {
    this->positionComponent = std::make_shared<PositionComponent>(id);

  } else {
    this->positionComponent = positionComponent;
  }
  this->positionComponent->setOwnerIdentity(id);
  this->positionComponent->setWidth(this->drawingComponent->getWidth());
  this->positionComponent->setHeight(this->drawingComponent->getHeight());

  this->collisionComponent = (collisionComponent == nullptr)
                                 ? std::make_shared<CollisionComponent>(id, positionComponent)
                                 : collisionComponent;
  this->collisionComponent->setOwnerIdentity(id);

  this->physicsComponent =
      (physicsComponent == nullptr) ? std::make_shared<SimplePhysicsComponent>(id) : physicsComponent;
  this->physicsComponent->setOwnerIdentity(id);
}

GameObject::~GameObject() = default;

DrawingComponent& GameObject::getDrawingComponent() const { return *(this->drawingComponent.get()); }
PhysicsComponent& GameObject::getPhysicsComponent() const { return *(this->physicsComponent.get()); }
PositionComponent& GameObject::getPositionComponent() const { return *(this->positionComponent.get()); }
CollisionComponent& GameObject::getCollisionComponent() const { return *(this->collisionComponent.get()); }

void GameObject::inferBoundingBoxFromTexture() {
  std::shared_ptr<Texture> texture = this->drawingComponent->getTexture();
  this->collisionComponent->height(texture->getHeight());
  this->collisionComponent->width(texture->getWidth());
}
