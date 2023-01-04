#include "GameObject.hh"

#include "DrawingProxy.hh"
#include "SDL2/SDL_image.h"
#include "ShootingProxy.hh"
#include "SpriteManager.hh"

GameObject::GameObject(const Vect2D& position, const Vect2D& velocity) : _velocity(velocity) {
  this->_positionComponent = std::unique_ptr<PositionComponent>(new PositionComponent(position));
}

GameObject::~GameObject() = default;

Vect2D GameObject::getPosition() const { return this->_positionComponent->getPosition(); }
PositionComponent& GameObject::getPositionComponent() const { return *this->_positionComponent; }

// IMovement
Vect2D GameObject::getVelocity() const { return this->_velocity; }
void GameObject::setVelocity(const Vect2D& velocity) { this->_velocity = velocity; }
void GameObject::move() {
  Vect2D currentPosition = this->_positionComponent->getPosition();
  this->_positionComponent->setPosition(currentPosition + this->_velocity);
}

// ICollision
bool GameObject::collisionTest(const GameObject& target) const {
  // TODO: Collision testing
  (void)target;
  return false;
}
