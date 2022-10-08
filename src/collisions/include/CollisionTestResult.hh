#pragma once

#include "Math.hh"
#include "PhysicsTypes.hh"

typedef struct Collision {
  shared_ptr<Identity> targetIdentity;
  CollisionAxis collisionAxis
} Collision;

class CollisionTestResult {
  /*
   * A CollisionTestResult stores information other objects can use to determine
   * what to do after a collision test.
   */
 public:
  CollisionTestResult(
      const shared_ptr<Identity> source, const shared_ptr<Vect2D> attemptedMove,
      const shared_ptr<set<shared_ptr<Identity>>> collisionObjectIDs);

  shared_ptr<set<shared_ptr<Identity>>> getCollisionObjectIDs() const;
  shared_ptr<Vect2D> getValidMove() const;
  shared_ptr<Identity> getFirstCollisionTarget() const;
  shared_ptr<Direction> getCollisionDirection() const;

 private:
  shared_ptr<Identity> source;
  shared_ptr<Vect2D> attemptedMove;
  shared_ptr<set<shared_ptr<Collision>>> collisions;
};
