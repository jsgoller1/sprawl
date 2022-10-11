#pragma once

#include "Identity.hh"
#include "Math.hh"
#include "PhysicsTypes.hh"

typedef struct Collision {
  shared_ptr<Identity> targetIdentity;
  CollisionAxis collisionAxis;
} Collision;

class CollisionTestResult {
  /*
   * A CollisionTestResult stores information other objects can use to determine
   * what to do after a collision test.
   */
 public:
  CollisionTestResult(const shared_ptr<Identity> source,
                      const shared_ptr<Vect2D> originalPosition,
                      const shared_ptr<Vect2D> attemptedPosition,
                      const shared_ptr<set<shared_ptr<Collision>>> collisions);

  shared_ptr<set<shared_ptr<Collision>>> getCollisions() const;
  shared_ptr<Vect2D> getValidPosition() const;

  shared_ptr<Identity> getFirstCollisionTarget() const;
  shared_ptr<Direction> getCollisionDirection() const;

 private:
  shared_ptr<Identity> source;
  shared_ptr<Vect2D> originalPosition;
  shared_ptr<Vect2D> attemptedPosition;
  shared_ptr<set<shared_ptr<Collision>>> collisions;
};
