#include "CollisionComponent.hh"

#include "Assumption.hh"
#include "PhysicsHelpers.hh"

CollisionComponent::CollisionComponent(const std::shared_ptr<Identity> ownerIdentity,
                                       const std::shared_ptr<PositionComponent> positionComponent,
                                       const PositionUnit height, const PositionUnit width,
                                       const bool collisionsEnabled)
    : Component(ownerIdentity),
      _positionComponent(positionComponent),
      _height(height),
      _width(width),
      _collisionsEnabled(collisionsEnabled) {}

std::shared_ptr<CollisionComponent> CollisionComponent::getptr() {
  return std::static_pointer_cast<CollisionComponent, Component>(this->shared_from_this());
}

std::shared_ptr<PositionComponent> CollisionComponent::positionComponent() const { return this->_positionComponent; }
void CollisionComponent::positionComponent(const std::shared_ptr<PositionComponent> positionComponent) {
  this->_positionComponent = positionComponent;
}

bool CollisionComponent::collisionsEnabled() const { return this->_collisionsEnabled; }
void CollisionComponent::collisionsEnabled(const bool setting) { this->_collisionsEnabled = setting; }

PositionUnit CollisionComponent::height() const { return this->_height; }
void CollisionComponent::height(const PositionUnit val) { this->_height = val; }
PositionUnit CollisionComponent::width() const { return this->_width; }
void CollisionComponent::width(const PositionUnit val) { this->_width = val; }

BoundingBox CollisionComponent::boundingBox(const Vect2D& offset) const {
  return BoundingBox(this->_positionComponent->getCenter() + offset, this->_height, this->_width);
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

std::shared_ptr<std::vector<Collision>> CollisionComponent::predictMovementCollisions(
    Vect2D positionDelta,
    const std::shared_ptr<std::set<std::shared_ptr<CollisionComponent>>> collisionComponents) const {
  /*
   * Checks if updating our position with positionDelta causes us to collide
   * with anything. Some possible edge cases:
   *
   * ## "Penetration" ( ͡° ͜ʖ ͡°)
   * If source is moving very fast and collides with an object
   * whose entire bounding box fits within the area the source moved over, no
   * collision occurs (this is due to the fact that we only test if the final
   * position causes a collision, not any position along the source's
   * trajectory). This is unlikely to happen (at least during the MVP) as most
   * objects are wide enough (e.g. 25-50 pixels) that nothing is going to move
   * that fast in a single game loop (500 pixels per second would be half the
   * screen in a second).
   * ## Solution
   * Test against the entire trajectory of the movement instead of the final
   * position (see notes).
   * ## Status
   * Unhandled
   *
   * ## "Lined up objects".
   * If the source's final position collides with multiple
   * objects in its final position, but each at a slightly difference distance.
   * Suppose source moves from (0,0) to (100,0) and its bounding box is 50px
   * wide. Thus, anything whose bounding box falls between (75,0) and (125,0)
   * causes a collision. Suppose there are 3 objects with bounding boxes whose
   * leftmost edges are at (110,*) (115,*), and (120,*). The source should only
   * collide with the first one, because after that collision, all movement
   * along the x axis is cancelled (though the target may then go on to collide
   * with the other two objects, but that will be resolved during its own
   * collision test). This case is also unlikely for the MVP. Most per-frame
   * movements are too small for this to occur with most objects, and in the
   * event that it does, the erroneous handling will be imperceptible.
   * ## Solution
   * Sort collision candidates from nearest to furthest from source
   * before testing; after any successful collision, update positionDelta with
   * the final position on relevant axes so that subsequent tests take into
   * account the previously occurring collision.
   * ## Solution 2
   * Still test all collisions as before, but before returning the collection to
   * the caller, remove any that are not the closest one.
   * ## Status
   * Handled
   *
   * ## "Stacked up objects".
   * Suppose source moves from (0,0) to (100,0) and its
   * bounding box is 50px wide. If we have 3 objects (each 10px tall/wide)
   * stacked on top of each other whose leftmost edges are at (110,*) but at
   * different heights, the source should register collisions with each of them.
   * We don't try to handle this edge case because it is again unlikely for the
   * MVP.
   * ## Solution
   * This case is resolved by solution 2 above as long as multiple collisions
   * can be the closest "ones".
   * ## Status
   * Handled
   */

  std::shared_ptr<std::vector<Collision>> collisions =
      std::shared_ptr<std::vector<Collision>>(new std::vector<Collision>());

  std::shared_ptr<Identity> ownerID = this->getOwnerIdentity();
  Vect2D originalPosition = this->_positionComponent->getCenter();
  Vect2D attemptedFinalPosition = Vect2D(originalPosition + positionDelta);

  for (std::shared_ptr<CollisionComponent> target : *collisionComponents) {
    if (this->isColliding(*target, positionDelta)) {
      std::shared_ptr<Identity> targetID = target->getOwnerIdentity();
      CollisionAxis collisionAxis = determineCollisionAxis(positionDelta, *target);
      LOG_DEBUG_SYS(COLLISIONS, "{0} collides with {1} on axis {2}", *this->getOwnerIdentity()->getEntityID(),
                    *targetID->getEntityID(), CollisionAxisToString(collisionAxis));
      LOG_DEBUG_SYS(COLLISIONS, "{0} (source) is at {1}", *this->getOwnerIdentity()->getEntityID(),
                    this->positionComponent()->getCenter().to_string());
      LOG_DEBUG_SYS(COLLISIONS, "{0} (target) is at {1}", *targetID->getEntityID(),
                    target->positionComponent()->getCenter().to_string());
      LOG_DEBUG_SYS(COLLISIONS, "{0} attempted to move to {1}", *this->getOwnerIdentity()->getEntityID(),
                    attemptedFinalPosition.to_string());
      Vect2D trueFinalPosition =
          this->determineFinalPosition(this->_positionComponent->getCenter(), positionDelta, *target, collisionAxis);
      LOG_DEBUG_SYS(COLLISIONS, "{0} actually moves {1}", *this->getOwnerIdentity()->getEntityID(),
                    trueFinalPosition.to_string());
      collisions->push_back(
          Collision(ownerID, targetID, originalPosition, positionDelta, trueFinalPosition, collisionAxis));

      attemptedFinalPosition = trueFinalPosition;
      // attemptedFinalPosition = closest(originalPosition, trueFinalPosition, attemptedFinalPosition);
    } else {
      LOG_DEBUG_SYS(COLLISIONS, "{0} does not collide with {1}", *this->getOwnerIdentity()->getEntityID(),
                    *target->getOwnerIdentity()->getEntityID());
    }
  }
  // Skip collisions with any objects that should not occur due to source
  // colliding with something else before it reaches the object.
  for (auto it = collisions->begin(); it != collisions->end();) {
    if ((*it).finalPosition() != attemptedFinalPosition) {
      collisions->erase(it);
    } else {
      it++;
    }
  }

  return collisions;
}

CollisionAxis CollisionComponent::determineCollisionAxis(const Vect2D& sourceMovement,
                                                         const CollisionComponent& target) const {
  /*
   * Determines which axis we needed to move along to cause the collision;
   * this has implications for collision resolution.
   */
  BoundingBox themBox = target.boundingBox();
  BoundingBox usBoxXOnly = this->boundingBox(sourceMovement.getXComponent());
  BoundingBox usBoxYOnly = this->boundingBox(sourceMovement.getYComponent());

  bool xCollision = themBox.checkCollision(usBoxXOnly);
  bool yCollision = themBox.checkCollision(usBoxYOnly);

  if (xCollision && !yCollision) {
    return X_ONLY;
  } else if (!xCollision && yCollision) {
    return Y_ONLY;
  } else if (xCollision && yCollision) {
    return X_OR_Y;
  } else {
    LOG_WARN_SYS(COLLISIONS, "{0} colliding due to X and Y movement.", *this->getOwnerIdentity()->getEntityID());
    return X_AND_Y;
  }
}

Vect2D CollisionComponent::determineFinalPosition(const Vect2D& sourcePosition, const Vect2D& positionDelta,
                                                  const CollisionComponent& target,
                                                  const CollisionAxis collisionAxis) const {
  /*
   * We know that us moving from sourcePosition to
   * sourcePosition+positionDelta causes a collision with target along
   * collisionAxis. So we need to figure out how far we can actually move
   * without causing a collision, and that's our final position.
   *
   * To calculate this, assume we're moving up (Y only) and we collide with the target; our center in the final position
   * should be beneath them:
   * - Start at the target's center
   * - Subtract half of their height; our center now sits on their bottom edge
   * - Subtract half of our height; our top edge now overlaps with their bottom edge.
   * - Subtract 1; our bounding boxes no longer overlap.
   *
   * For cases of colliding from above, left, or right, just do the same but with width instead of height or add instead
   * of subtract where needed.
   */

  // TODO: I don't like this reaching-into-implementation here; I feel like
  // we should be calling other methods that know about boxes.
  Vect2D finalPosition = sourcePosition + positionDelta;
  Vect2D targetCenter = target.positionComponent()->getCenter();
  Rectangle usBox = this->boundingBox().box();
  LOG_DEBUG_SYS(COLLISIONS, "{0} (source) bbox: {1}", *this->getOwnerIdentity()->getEntityID(), usBox.toString());
  Rectangle targetBox = target.boundingBox().box();
  LOG_DEBUG_SYS(COLLISIONS, "{0} (target) bbox: {1}", *target.getOwnerIdentity()->getEntityID(), targetBox.toString());

  // TODO: There is a bug here with X_OR_Y movements causing finalPosition inside other objects
  // TODO: Actually, this doesn't ensure that the final position doesn't put us inside another object;

  LOG_DEBUG_SYS(COLLISIONS, "{0} (target) is {1} {2} (source)", *target.getOwnerIdentity()->getEntityID(),
                (target.positionComponent()->getCenter().above(sourcePosition) ? "above" : "below"),
                *this->getOwnerIdentity()->getEntityID());
  if (collisionAxis != X_ONLY) {
    if (targetCenter.above(sourcePosition)) {
      finalPosition.y(targetCenter.y() - (targetBox.height() / 2.0) - (usBox.height() / 2.0) - 1.0);
    } else {
      finalPosition.y(targetCenter.y() + (targetBox.height() / 2.0) + (usBox.height() / 2.0) + 1.0);
    }
  }

  LOG_DEBUG_SYS(COLLISIONS, "{0} (target) is {1} {2}'s (source)", *target.getOwnerIdentity()->getEntityID(),
                (target.positionComponent()->getCenter().leftOf(sourcePosition) ? "left of" : "right of"),
                *this->getOwnerIdentity()->getEntityID());
  if (collisionAxis != Y_ONLY) {
    if (targetCenter.rightOf(sourcePosition)) {
      finalPosition.x(targetCenter.x() - (targetBox.width() / 2.0) - (usBox.width() / 2.0) - 1.0);
    } else {
      finalPosition.x(targetCenter.x() + (targetBox.width() / 2.0) + (usBox.width() / 2.0) + 1.0);
    }
  }
  return finalPosition;
}
