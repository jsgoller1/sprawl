#include "CharacterPhysicsComponent.hh"

CharacterPhysicsComponent::CharacterPhysicsComponent(
    const shared_ptr<PositionComp> positionComp,
    const shared_ptr<BoundingBoxParams> boundingBoxParams,
    const bool collisionsSetting, const bool gravitySetting)
    : PhysicsComponent(positionComp, boundingBoxParams, collisionsSetting,
                       gravitySetting) {
  this->moveSpeed = 10.0;
  this->jumpSpeed = 10.0;
}

void CharacterPhysicsComponent::applyJumpForce() {}
void CharacterPhysicsComponent::applyMovementForce(
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

  if (*direction == *Direction::Left()) {
    if (this->velocity->x <= -this->moveSpeed) {
      // If we're already moving as fast as we need to be (or faster),
      // we don't need to add any additional force.
      return;
    }
    // Otherwise, cancel any existing velocity and acceleration, and add a
    // single force that will immediately accelerate us to top speed.
    // TODO: All GameObjects presently have unit mass, so we can achieve
    // our maximum velocity by applying a force equal to the desired velocity
    // for 1 unit of time (plus additional force to counteract drag). This will
    // not work once we have different masses.

    this->velocity->x = 0;
    this->acceleration->x = 0;
    shared_ptr<Vect2D> impulseForce = shared_ptr<Vect2D>(new Vect2D(-1.0, 0.0));
    *impulseForce *= this->moveSpeed;
    shared_ptr<Vect2D> counterDragForce =
        calculateDragForce(impulseForce, this->getCurrentDragCoeff());
    counterDragForce->invert();
    *impulseForce += counterDragForce;
    this->applyForce(impulseForce);

  } else if (*direction == *Direction::Right()) {
    if (this->velocity->x >= this->moveSpeed) {
      return;
    }
    this->velocity->x = 0;
    this->acceleration->x = 0;
    shared_ptr<Vect2D> impulseForce = shared_ptr<Vect2D>(new Vect2D(1.0, 0.0));
    *impulseForce *= this->moveSpeed;
    shared_ptr<Vect2D> counterDragForce =
        calculateDragForce(impulseForce, this->getCurrentDragCoeff());
    counterDragForce->invert();
    *impulseForce += counterDragForce;
    this->applyForce(impulseForce);
  } else {
    // TODO: Log a warning, nothing to do here.
  }
}
