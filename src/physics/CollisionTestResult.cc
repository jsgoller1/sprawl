#include "CollisionTestResult.hh"

CollisionTestResult::CollisionTestResult(
    const shared_ptr<Identity> source,
    const shared_ptr<Vect2D> originalPosition,
    const shared_ptr<Vect2D> attemptedMove,
    const shared_ptr<Vect2D> finalPosition,
    const shared_ptr<set<shared_ptr<Collision>>> collisions)
    : source(source),
      originalPosition(originalPosition),
      attemptedMove(attemptedMove),
      finalPosition(finalPosition),
      collisions(collisions) {}

shared_ptr<Identity> CollisionTestResult::getSource() const {
  return this->source;
}
shared_ptr<Vect2D> CollisionTestResult::getOriginalPosition() const {
  return this->originalPosition;
}
shared_ptr<Vect2D> CollisionTestResult::getAttemptedMove() const {
  return this->attemptedMove;
}
shared_ptr<Vect2D> CollisionTestResult::getFinalPosition() const {
  return this->finalPosition;
}
shared_ptr<set<shared_ptr<Collision>>> CollisionTestResult::getCollisions()
    const {
  return this->collisions;
}
bool CollisionTestResult::empty() { return this->collisions->empty(); }
int CollisionTestResult::size() { return this->collisions->size(); }
