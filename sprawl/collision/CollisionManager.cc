#include "CollisionManager.hh"

#include "Time.hh"
#include "Types.hh"

void CollisionManager::gameLoopUpdate(const time_ms duration) { (void)duration; }

/*
 * TODO: CollisionManager code commented out for now; the right way to handle this will be with the yet-to
 * be implemented event bus.
 */

// void CollisionManager::predictMovementCollisions(const Vect2D& positionDelta,
//                                                  std::unordered_set<std::shared_ptr<Actor>>& collisionCandidates,
//                                                  std::vector<Collision>& collisions) const {
//   /*
//    * Checks if updating our position with positionDelta causes us to collide
//    * with anything. Some possible edge cases:
//    *
//    * ## "Penetration" ( ͡° ͜ʖ ͡°)
//    * If source is moving very fast and collides with an object
//    * whose entire bounding box fits within the area the source moved over, no
//    * collision occurs (this is due to the fact that we only test if the final
//    * position causes a collision, not any position along the source's
//    * trajectory). This is unlikely to happen (at least during the MVP) as most
//    * objects are wide enough (e.g. 25-50 pixels) that nothing is going to move
//    * that fast in a single game loop (500 pixels per second would be half the
//    * screen in a second).
//    * ## Solution
//    * Test against the entire trajectory of the movement instead of the final
//    * position (see notes).
//    * ## Status
//    * Unhandled
//    *
//    * ## "Lined up objects".
//    * If the source's final position collides with multiple
//    * objects in its final position, but each at a slightly difference distance.
//    * Suppose source moves from (0,0) to (100,0) and its bounding box is 50px
//    * wide. Thus, anything whose bounding box falls between (75,0) and (125,0)
//    * causes a collision. Suppose there are 3 objects with bounding boxes whose
//    * leftmost edges are at (110,*) (115,*), and (120,*). The source should only
//    * collide with the first one, because after that collision, all movement
//    * along the x axis is cancelled (though the target may then go on to collide
//    * with the other two objects, but that will be resolved during its own
//    * collision test). This case is also unlikely for the MVP. Most per-frame
//    * movements are too small for this to occur with most objects, and in the
//    * event that it does, the erroneous handling will be imperceptible.
//    * ## Solution
//    * Sort collision candidates from nearest to furthest from source
//    * before testing; after any successful collision, update positionDelta with
//    * the final position on relevant axes so that subsequent tests take into
//    * account the previously occurring collision.
//    * ## Solution 2
//    * Still test all collisions as before, but before returning the collection to
//    * the caller, remove any that are not the closest one.
//    * ## Status
//    * Handled
//    *
//    * ## "Stacked up objects".
//    * Suppose source moves from (0,0) to (100,0) and its
//    * bounding box is 50px wide. If we have 3 objects (each 10px tall/wide)
//    * stacked on top of each other whose leftmost edges are at (110,*) but at
//    * different heights, the source should register collisions with each of them.
//    * We don't try to handle this edge case because it is again unlikely for the
//    * MVP.
//    * ## Solution
//    * This case is resolved by solution 2 above as long as multiple collisions
//    * can be the closest "ones".
//    * ## Status
//    * Handled
//    */

//   std::shared_ptr<std::vector<Collision>> collisions =
//       std::shared_ptr<std::vector<Collision>>(new std::vector<Collision>());

//   Vect2D originalPosition = this->_positionComponent->getCenter();
//   Vect2D attemptedFinalPosition = Vect2D(originalPosition + positionDelta);

//   for (std::shared_ptr<CollisionComponent> target : *collisionComponents) {
//     if (this->isColliding(*target, positionDelta)) {
//       CollisionAxis collisionAxis = determineCollisionAxis(positionDelta, *target);
//       LOG_DEBUG_SYS(COLLISIONS, "{0} collides with {1} on axis {2}", this->toString(), target->toString(),
//                     CollisionAxisToString(collisionAxis));
//       LOG_DEBUG_SYS(COLLISIONS, "{0} (source) is at {1}", this->toString(),
//                     this->positionComponent()->getCenter().to_string());
//       LOG_DEBUG_SYS(COLLISIONS, "{0} (target) is at {1}", this->toString(),
//                     target->positionComponent()->getCenter().to_string());
//       LOG_DEBUG_SYS(COLLISIONS, "{0} attempted to move to {1}", this->toString(),
//       attemptedFinalPosition.to_string()); Vect2D trueFinalPosition =
//           this->determineFinalPosition(this->_positionComponent->getCenter(), positionDelta, *target, collisionAxis);
//       LOG_DEBUG_SYS(COLLISIONS, "{0} actually moves {1}", this->toString(), trueFinalPosition.to_string());
//       collisions->push_back(Collision(this->getOwner(), target->getOwner(), originalPosition, positionDelta,
//                                       trueFinalPosition, collisionAxis));

//       attemptedFinalPosition = trueFinalPosition;
//       // attemptedFinalPosition = closest(originalPosition, trueFinalPosition, attemptedFinalPosition);
//     } else {
//       LOG_DEBUG_SYS(COLLISIONS, "{0} does not collide with {1}", this->toString(), target->toString());
//     }
//   }
//   // Skip collisions with any objects that should not occur due to source
//   // colliding with something else before it reaches the object.
//   for (auto it = collisions->begin(); it != collisions->end();) {
//     if ((*it).finalPosition() != attemptedFinalPosition) {
//       collisions->erase(it);
//     } else {
//       it++;
//     }
//   }

//   return collisions;
// }

// CollisionAxis CollisionManager::determineCollisionAxis(const Vect2D& sourceMovement,
//                                                        const CollisionComponent& target) const {
//   /*
//    * Determines which axis we needed to move along to cause the collision;
//    * this has implications for collision resolution.
//    */
//   BoundingBox themBox = target.boundingBox();
//   BoundingBox usBoxXOnly = this->boundingBox(sourceMovement.getXComponent());
//   BoundingBox usBoxYOnly = this->boundingBox(sourceMovement.getYComponent());

//   bool xCollision = themBox.checkCollision(usBoxXOnly);
//   bool yCollision = themBox.checkCollision(usBoxYOnly);

//   if (xCollision && !yCollision) {
//     return X_ONLY;
//   } else if (!xCollision && yCollision) {
//     return Y_ONLY;
//   } else if (xCollision && yCollision) {
//     return X_OR_Y;
//   } else {
//     LOG_WARN_SYS(COLLISIONS, "{0} colliding due to X and Y movement.", this->toString());
//     return X_AND_Y;
//   }
// }

// Vect2D CollisionManager::determineFinalPosition(const Vect2D& sourcePosition, const Vect2D& positionDelta,
//                                                 const CollisionComponent& target,
//                                                 const CollisionAxis collisionAxis) const {
//   /*
//    * We know that us moving from sourcePosition to
//    * sourcePosition+positionDelta causes a collision with target along
//    * collisionAxis. So we need to figure out how far we can actually move
//    * without causing a collision, and that's our final position.
//    *
//    * To calculate this, assume we're moving up (Y only) and we collide with the target; our center in the final
//    position
//    * should be beneath them:
//    * - Start at the target's center
//    * - Subtract half of their height; our center now sits on their bottom edge
//    * - Subtract half of our height; our top edge now overlaps with their bottom edge.
//    * - Subtract 1; our bounding boxes no longer overlap.
//    *
//    * For cases of colliding from above, left, or right, just do the same but with width instead of height or add
//    instead
//    * of subtract where needed.
//    */

//   // TODO: I don't like this reaching-into-implementation here; I feel like
//   // we should be calling other methods that know about boxes.
//   Vect2D finalPosition = sourcePosition + positionDelta;
//   Vect2D targetCenter = target.positionComponent()->getCenter();
//   Rectangle usBox = this->boundingBox().box();
//   LOG_DEBUG_SYS(COLLISIONS, "{0} (source) bbox: {1}", this->toString(), usBox.toString());
//   Rectangle targetBox = target.boundingBox().box();
//   LOG_DEBUG_SYS(COLLISIONS, "{0} (target) bbox: {1}", target.toString(), targetBox.toString());

//   // TODO: There is a bug here with X_OR_Y movements causing finalPosition inside other objects
//   // TODO: Actually, this doesn't ensure that the final position doesn't put us inside another object;

//   LOG_DEBUG_SYS(COLLISIONS, "{0} (target) is {1} {2} (source)", target.toString(),
//                 (target.positionComponent()->getCenter().above(sourcePosition) ? "above" : "below"),
//                 this->toString());
//   if (collisionAxis != X_ONLY) {
//     if (targetCenter.above(sourcePosition)) {
//       finalPosition.y(targetCenter.y() - (targetBox.getHeight() / 2.0) - (usBox.getHeight() / 2.0) - 1.0);
//     } else {
//       finalPosition.y(targetCenter.y() + (targetBox.getHeight() / 2.0) + (usBox.getHeight() / 2.0) + 1.0);
//     }
//   }

//   LOG_DEBUG_SYS(COLLISIONS, "{0} (target) is {1} {2}'s (source)", target.toString(),
//                 (target.positionComponent()->getCenter().leftOf(sourcePosition) ? "left of" : "right of"),
//                 this->toString());
//   if (collisionAxis != Y_ONLY) {
//     if (targetCenter.rightOf(sourcePosition)) {
//       finalPosition.x(targetCenter.x() - (targetBox.getWidth() / 2.0) - (usBox.getWidth() / 2.0) - 1.0);
//     } else {
//       finalPosition.x(targetCenter.x() + (targetBox.getWidth() / 2.0) + (usBox.getWidth() / 2.0) + 1.0);
//     }
//   }
//   return finalPosition;
// }

// /*
//  * FOR DEBUGGING ONLY. Tests whether any items currently managed by the physics manager are actually overlapping, and
//  * thus would trigger a collision without moving. This should _never_ occur, so this function should in theory always
//  * return true. This function is O(n^2) (very slow); this will crush framerate!
//  */
// bool PhysicsManager::diagnosticNoOverlaps() const {
//   std::vector<std::shared_ptr<CollisionComponent>> components = std::vector<std::shared_ptr<CollisionComponent>>();
//   for (auto comp : *this->managedActors) {
//     components.push_back(comp.second->collisionComponent);
//   }

//   for (unsigned long i = 0; i < components.size(); i++) {
//     CollisionComponent source = *components[i];
//     for (unsigned long j = i + 1; j < components.size(); j++) {
//       CollisionComponent target = *components[j];
//       if (source.isColliding(target, Vect2D::zero())) {
//         LOG_ERROR_SYS(COLLISIONS, "{} is overlapping with {}!", source.getOwnerIdentity()->getEntityID(),
//                       target.getOwnerIdentity()->getEntityID());
//         return false;
//       }
//     }
//   }
//   return true;
// }
