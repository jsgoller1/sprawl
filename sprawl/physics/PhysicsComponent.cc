#include "PhysicsComponent.hh"

PhysicsComponent::PhysicsComponent(const std::shared_ptr<Identity> ownerIdentity, const PositionUnit maxSpeed,
                                   const PositionUnit minSpeed, const Vect2D velocity)
    : Component(ownerIdentity), _maxSpeed(maxSpeed), _minSpeed(minSpeed), _velocity(velocity) {}

PhysicsComponent::~PhysicsComponent() = default;

std::shared_ptr<PhysicsComponent> PhysicsComponent::getptr() { return this->shared_from_this(); }

PositionUnit PhysicsComponent::getMaxSpeed() const { return this->_maxSpeed; }
void PhysicsComponent::setMaxSpeed(const PositionUnit maxSpeed) { this->_maxSpeed = maxSpeed; }
PositionUnit PhysicsComponent::getMinSpeed() { return this->_minSpeed; }
void PhysicsComponent::setMinSpeed(const PositionUnit minSpeed) { this->_minSpeed = minSpeed; }
Vect2D PhysicsComponent::getVelocity() const { return this->_velocity; }
void PhysicsComponent::setVelocity(const Vect2D& velocity) { this->_velocity = velocity; }
std::shared_ptr<PhysicsManager> PhysicsComponent::getManager() const { return this->_manager; }
void PhysicsComponent::setManager(const std::shared_ptr<PhysicsManager> manager) { this->_manager = manager; }
