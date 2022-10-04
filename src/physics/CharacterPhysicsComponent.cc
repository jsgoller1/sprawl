#include "CharacterPhysicsComponent.hh"

// NOTE: See note in header about name hiding; I hate this.
shared_ptr<CharacterPhysicsComponent> CharacterPhysicsComponent::getptr() {
  return static_pointer_cast<CharacterPhysicsComponent, PhysicsComponent>(
      this->shared_from_this());
}

CharacterPhysicsComponent::CharacterPhysicsComponent(
    const GameObjectNameSPtr ownerName,
    const shared_ptr<PositionComp> positionComp,
    const shared_ptr<BoundingBoxParams> boundingBoxParams,
    const bool collisionsSetting, const bool gravitySetting)
    : PhysicsComponent(ownerName, positionComp, boundingBoxParams,
                       collisionsSetting, gravitySetting) {}

void CharacterPhysicsComponent::applyJumpForce() {}
void CharacterPhysicsComponent::applyMovementForce(
    const shared_ptr<Direction> direction) {
  PositionUnit speed = this->getMaxSpeed();
  speed *= (*direction == *Direction::Left()) ? -1.0 : 1.0;
  shared_ptr<Vect2D> moveForce = shared_ptr<Vect2D>(new Vect2D(speed, 0.0));
  this->applyForce(moveForce);
}
void CharacterPhysicsComponent::applyMovementForceOld(
    const shared_ptr<Direction> direction) {
  // If the character is not already moving in the desired direction at max
  // velocity, apply sufficient force for them to accelerate to max velocity and
  // overcome drag.

  // NOTE: If a character begins moving left, we zero any right-ward velocity
  // they may have had and vice versa; this is a hack that saves us from having
  // to back-solve how much left-ward force we'd have to add to accelerate left
  // until we reach desired velocity. We do not zero the net force; e.g. if a
  // character is trying to move left but is getting collided with, they still
  // should be pushed in whatever direction the collision pushed them (net force
  // will be zeroed after one update from the physics manager, anyway).

  // Cancel any existing velocity and acceleration, and add a
  // single force that will immediately accelerate us to top speed.
  // TODO: All GameObjects presently have unit mass, so we can achieve
  // our maximum velocity by applying a force equal to the desired velocity
  // for 1 unit of time (plus additional force to counteract drag). This
  // will not work once we have different masses.

  // Do nothing if we're somehow told to move in an illegal direction
  if (not(*direction == *Direction::Left()) &&
      not(*direction == *Direction::Right())) {
    return;
  }
  // If we're already moving as fast as we need to be (or faster),
  // we don't need to add any additional force, so we can bail out here.
  if (*direction == *Direction::Left()
          ? this->getVelocity()->x <= -this->getMaxSpeed()
          : this->getVelocity()->x >= this->getMaxSpeed()) {
    return;
  }
  // Otherwise, zero our existing velocity / acceleration and prepare an impulse
  // force in the desired direction
  // this->velocity->x = 0;
  this->getAcceleration()->x = 0;
  real impulseDirection =
      (*direction == *Direction::Left() ? -this->getMaxSpeed()
                                        : this->getMaxSpeed());
  shared_ptr<Vect2D> impulseForce =
      shared_ptr<Vect2D>(new Vect2D(impulseDirection, 0.0));

  // Apply a bit extra force to ensure whatever drag we experience will be
  // cancelled out so we get to our top velocity.
  shared_ptr<Vect2D> counterDragForce =
      calculateDragForce(impulseForce, this->getDragCoefficient());
  counterDragForce->invert();
  *impulseForce += counterDragForce;
  this->applyForce(impulseForce);
}
