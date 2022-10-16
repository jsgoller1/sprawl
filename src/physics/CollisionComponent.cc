#include "CollisionComponent.hh"

CollisionComponent::CollisionComponent(
    const shared_ptr<Identity> ownerIdentity,
    const shared_ptr<PositionComponent> positionComponent,
    const shared_ptr<BoundingBoxParams> boundingBoxParams,
    const bool collisionsEnabled)
    : positionComponent(positionComponent),
      boundingBoxParams(boundingBoxParams),
      collisionsEnabled(collisionsEnabled),
      Component(ownerIdentity) {}

shared_ptr<CollisionComponent> CollisionComponent::getptr() {
  return static_pointer_cast<CollisionComponent, Component>(
      this->shared_from_this());
}

shared_ptr<BoundingBox> CollisionComponent::getBoundingBox(
    const shared_ptr<Vect2D> offset) const {
  /*
   * Create a bounding box centered on the object by default, or optionally
   * offset by a provided distance.
   */
  shared_ptr<Vect2D> trueOffset = (offset == nullptr) ? Vect2D::zero() : offset;
  return shared_ptr<BoundingBox>(
      new BoundingBox(*(this->positionComponent->getCenter()) + *trueOffset,
                      this->boundingBoxParams));
};

bool CollisionComponent::isColliding(
    /*
     * Calculates bounding boxes around this component and the target component
     * (optional: if provided, applys offsets to center of each first), then
     * returns if they overlap.
     */
    const shared_ptr<CollisionComponent> targetComponent,
    const shared_ptr<Vect2D> sourceOffset,
    const shared_ptr<Vect2D> targetOffset) const {
  if (this == targetComponent.get()) {
    // We are never colliding with ourselves
    return false;
  }
  shared_ptr<BoundingBox> usBox = this->getBoundingBox(sourceOffset);
  shared_ptr<BoundingBox> themBox =
      targetComponent->getBoundingBox(targetOffset);
  return usBox->checkCollision(themBox);
}

shared_ptr<set<shared_ptr<CollisionComponent>>>
CollisionComponent::isCollidingBatched(
    const shared_ptr<Vect2D> sourceOffset,
    const shared_ptr<set<
        shared_ptr<pair<shared_ptr<CollisionComponent>, shared_ptr<Vect2D>>>>>
        targetOffsetPairs) {
  shared_ptr<set<shared_ptr<CollisionComponent>>> targetSet =
      shared_ptr<set<shared_ptr<CollisionComponent>>>(
          new set<shared_ptr<CollisionComponent>>());

  shared_ptr<CollisionComponent> target;
  shared_ptr<Vect2D> targetOffset;
  for (auto targetOffsetPair : *targetOffsetPairs) {
    target = targetOffsetPair->first;
    targetOffset = targetOffsetPair->second;
    if (this->isColliding(target, sourceOffset, targetOffset)) {
      targetSet->insert(target);
    }
  }
  return targetSet;
}

bool CollisionComponent::isTrajectoryColliding(
    const shared_ptr<Vect2D> positionDelta,
    const shared_ptr<CollisionComponent> targetComponent) {
  /*
   * Treats positionDelta as the trajectory along which this
   * component will move and determines if at any point along the trajectory it
   * collides with targetComponent.
   *
   * To accomplish this, we only consider the center point of the collision
   * source, then
   */
}

shared_ptr<CollisionTestResult> CollisionComponent::predictMovementCollision(
    const shared_ptr<Vect2D> positionDelta,
    const shared_ptr<set<shared_ptr<CollisionComponent>>> collisionCandidates) {
  /*
   * Tests if a particular movement would cause an object to collide with
   * another object.
   */
  shared_ptr<set<shared_ptr<CollisionComponent>>> collidingComponent =
      this->testCollisions(positionDelta, collisionCandidates);

  shared_ptr<set<shared_ptr<Collision>>> finalizedCollisionSet =
      shared_ptr<set<shared_ptr<Collision>>>(new set<shared_ptr<Collision>>());

  for (shared_ptr<CollisionComponent> target : *collidingComponent) {
    finalizedCollisionSet->insert(shared_ptr<Collision>(new Collision{
        .targetIdentity = target->getOwnerIdentity(),
        .collisionAxis = determineCollisionAxis(positionDelta, target)}));
  }

  return shared_ptr<CollisionTestResult>(new CollisionTestResult(
      this->getOwnerIdentity(), this->positionComponent->getCenter(),
      positionDelta, finalizedCollisionSet));
}

CollisionAxis CollisionComponent::determineCollisionAxis(
    const shared_ptr<Vect2D> sourceMovement,
    const shared_ptr<CollisionComponent> target) {
  shared_ptr<Vect2D> usCenter = this->getPositionComponent()->getCenter();
  shared_ptr<Vect2D> themCenter = target->getPositionComponent()->getCenter();
  bool xCollision = gte(usCenter->x, themCenter->x) &&
                    gte(themCenter->x, usCenter->x + sourceMovement->x);
  bool yCollision = gte(usCenter->y, themCenter->y) &&
                    gte(themCenter->y, usCenter->y + sourceMovement->y);
  if (xCollision && !yCollision) {
    return X_ONLY;
  } else if (!xCollision && yCollision) {
    return Y_ONLY;
  } else if (xCollision && yCollision) {
    return X_OR_Y;
  } else {
    return X_AND_Y;
  }
}

/*
shared_ptr<Vect2D> CollisionTestResult::getValidPosition() const {
  // Get the position the collision source should wind up in given the
  // collisions its movement would cause.
  // TODO: For now, let's just have the "valid move" be not moving at all, i.e.
  // the original position the object was in. This might result in
  // "forcefielding", but we can address it later.
  shared_ptr<Vect2D> finalPosition = shared_ptr<Vect2D>(
      new Vect2D(*this->originalPosition + *this->attemptedMove));

  for (auto collision : *this->collisions) {
    switch (collision->collisionAxis) {
      case X_ONLY:
        finalPosition->x = originalPosition->x;
        break;
      case Y_ONLY:
        finalPosition->y = originalPosition->y;
        break;
      case X_AND_Y:
      case X_OR_Y:
        finalPosition->x = originalPosition->x;
        finalPosition->y = originalPosition->y;
        break;
    }
  }

  return finalPosition;
}
*/
