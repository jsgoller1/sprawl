#include "CollisionTestResult.hh"

CollisionTestResult::CollisionTestResult(
    const shared_ptr<Identity> source,
    const shared_ptr<Vect2D> originalPosition,
    const shared_ptr<Vect2D> attemptedPosition,
    const shared_ptr<set<shared_ptr<Collision>>> collisions)
    : source(source),
      originalPosition(originalPosition),
      attemptedPosition(attemptedPosition),
      collisions(collisions) {}

shared_ptr<set<shared_ptr<Collision>>> CollisionTestResult::getCollisions()
    const {
  return this->collisions;
}

shared_ptr<Vect2D> CollisionTestResult::getValidPosition() const {
  // Get the position the collision source should wind up in given the
  // collisions its movement would cause.
  // TODO: For now, let's just have the "valid move" be not moving at all, i.e.
  // the original position the object was in. This might result in
  // "forcefielding", but we can address it later.
  return (collisions->empty()) ? this->attemptedPosition
                               : this->originalPosition;
}
