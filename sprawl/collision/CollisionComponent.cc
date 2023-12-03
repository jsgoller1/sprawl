#include "CollisionComponent.hh"

#include "Actor.hh"
#include "Assumption.hh"
#include "CollisionManager.hh"
#include "PhysicsHelpers.hh"

CollisionComponent::CollisionComponent(const PositionUnit height, const PositionUnit width,
                                       const bool collisionsEnabled)
    : Component(), _height(height), _width(width), _collisionsEnabled(collisionsEnabled) {}

CollisionComponent::~CollisionComponent() { this->managerUnregister(); }

std::string CollisionComponent::toString() const {
  return fmt::format("CollisionComponent({})", this->getOwner()->toString());
}

void CollisionComponent::managerRegister() { CollisionManager::instance().manage(this->getOwner()); }
void CollisionComponent::managerUnregister() { CollisionManager::instance().unmanage(this->getOwner()); }

bool CollisionComponent::collisionsEnabled() const { return this->_collisionsEnabled; }
void CollisionComponent::collisionsEnabled(const bool setting) { this->_collisionsEnabled = setting; }

PositionUnit CollisionComponent::height() const { return this->_height; }
void CollisionComponent::height(const PositionUnit val) { this->_height = val; }
PositionUnit CollisionComponent::width() const { return this->_width; }
void CollisionComponent::width(const PositionUnit val) { this->_width = val; }

BoundingBox CollisionComponent::boundingBox(const Vect2D& offset) const {
  return BoundingBox(this->getOwner()->getComponent<PositionComponent>()->getCenter() + offset, this->_height,
                     this->_width);
};

bool CollisionComponent::isColliding(const Vect2D& point, const Vect2D& sourceOffset) const {
  return this->boundingBox(sourceOffset).checkCollision(point);
}

bool CollisionComponent::isColliding(const Line& line, const Vect2D& sourceOffset) const {
  return this->boundingBox(sourceOffset).checkCollision(line);
}

bool CollisionComponent::isColliding(const CollisionComponent& targetComponent, const Vect2D& sourceOffset) const {
  if (this == &targetComponent) {
    return false;
  }
  return this->boundingBox(sourceOffset).checkCollision(targetComponent.boundingBox());
}
