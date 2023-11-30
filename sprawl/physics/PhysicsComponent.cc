#include "PhysicsComponent.hh"

#include "PhysicsManager.hh"

PhysicsComponent::PhysicsComponent(const std::weak_ptr<Actor> owner, const PositionUnit maxSpeed,
                                   const PositionUnit minSpeed, const Vect2D velocity)
    : Component(owner), _maxSpeed(maxSpeed), _minSpeed(minSpeed), _velocity(velocity) {
  PhysicsManager::instance().manage(this->getOwner());
}

PhysicsComponent::~PhysicsComponent() { PhysicsManager::instance().unmanage(this->getOwner()); }

PositionUnit PhysicsComponent::getMaxSpeed() const { return this->_maxSpeed; }
void PhysicsComponent::setMaxSpeed(const PositionUnit maxSpeed) { this->_maxSpeed = maxSpeed; }
PositionUnit PhysicsComponent::getMinSpeed() { return this->_minSpeed; }
void PhysicsComponent::setMinSpeed(const PositionUnit minSpeed) { this->_minSpeed = minSpeed; }
Vect2D PhysicsComponent::getVelocity() const { return this->_velocity; }
void PhysicsComponent::setVelocity(const Vect2D& velocity) { this->_velocity = velocity; }
