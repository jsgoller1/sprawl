#include "PhysicsComponent.hh"

#include "PhysicsManager.hh"

PhysicsComponent::PhysicsComponent(const std::shared_ptr<Identity> ownerIdentity, const PositionUnit maxSpeed,
                                   const PositionUnit minSpeed, const Vect2D velocity)
    : Component(ownerIdentity), _maxSpeed(maxSpeed), _minSpeed(minSpeed), _velocity(velocity) {}

PhysicsComponent::~PhysicsComponent() = default;

PositionUnit PhysicsComponent::getMaxSpeed() const { return this->_maxSpeed; }
void PhysicsComponent::setMaxSpeed(const PositionUnit maxSpeed) { this->_maxSpeed = maxSpeed; }
PositionUnit PhysicsComponent::getMinSpeed() { return this->_minSpeed; }
void PhysicsComponent::setMinSpeed(const PositionUnit minSpeed) { this->_minSpeed = minSpeed; }
Vect2D PhysicsComponent::getVelocity() const { return this->_velocity; }
void PhysicsComponent::setVelocity(const Vect2D& velocity) { this->_velocity = velocity; }
const PhysicsManager& PhysicsComponent::getManager() const { return *this->_manager; }
void PhysicsComponent::setManager(const PhysicsManager& manager) { this->_manager = manager.shared_from_this(); }
