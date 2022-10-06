#include "PhysicsComponent.hh"

PhysicsComponent::PhysicsComponent(
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<BoundingBox> boundingBox, const bool collisionsSetting,
    const bool gravitySetting) {
  this->positionComponent = positionComponent;
  this->boundingBox = boundingBox;
  this->gravityEnabled = gravitySetting;
  this->collisionsEnabled = collisionsSetting;
  this->velocity = shared_ptr<Point>(new Point{.x = 0, .y = 0});
}

shared_ptr<PhysicsComponent> PhysicsComponent::getptr() {
  return this->shared_from_this();
}

bool PhysicsComponent::hasCollisions() { return this->collisionsEnabled; }
void PhysicsComponent::enableCollisions(const bool setting) {
  this->collisionsEnabled = setting;
}
bool PhysicsComponent::hasGravity() { return this->gravityEnabled; }
void PhysicsComponent::enableGravity(const bool setting) {
  this->gravityEnabled = setting;
}

void PhysicsComponent::setVelocity(const shared_ptr<Point> velocity) {
  this->velocity = velocity;
}
shared_ptr<Point> PhysicsComponent::getVelocity() { return this->velocity; }

void PhysicsComponent::addVelocity(const shared_ptr<Point> velocity) {
  this->velocity->x += velocity->x;
  this->velocity->y += velocity->y;
}

shared_ptr<PhysicsManager> PhysicsComponent::getManager() {
  return this->manager;
}
void PhysicsComponent::setManager(const shared_ptr<PhysicsManager> manager) {
  this->manager = manager;
}

void PhysicsComponent::setBoundingBox(const shared_ptr<BoundingBox> box) {
  this->boundingBox = box;
}

void PhysicsComponent::setBoundingBox(const PositionUnit height,
                                      const PositionUnit width) {
  this->boundingBox = shared_ptr<BoundingBox>(
      new BoundingBox{.height = height, .width = width});
}

shared_ptr<BoundingBox> PhysicsComponent::getBoundingBox() {
  return this->boundingBox;
}

bool PhysicsComponent::isColliding() {
  shared_ptr<vector<shared_ptr<PhysicsComponent>>> colliding =
      this->manager->getAllColliding(this->getptr());
  return !(colliding->empty());
}

shared_ptr<Point> PhysicsComponent::getCenter() {
  return this->positionComponent->getCenter();
}

void PhysicsComponent::move(shared_ptr<Point> direction) {
  this->positionComponent->move(direction);
}
