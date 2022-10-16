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
                      const shared_ptr<Vect2D> attemptedMove,
                      const shared_ptr<Vect2D> finalPosition,
                      const shared_ptr<set<shared_ptr<Collision>>> collisions);

  shared_ptr<Identity> getSource() const;
  shared_ptr<Vect2D> getOriginalPosition() const;
  shared_ptr<Vect2D> getAttemptedMove() const;
  shared_ptr<Vect2D> getFinalPosition() const;
  shared_ptr<set<shared_ptr<Collision>>> getCollisions() const;
  bool empty();
  int size();

 private:
  shared_ptr<Identity> source;
  shared_ptr<Vect2D> originalPosition;
  shared_ptr<Vect2D> attemptedMove;
  shared_ptr<Vect2D> finalPosition;
  shared_ptr<set<shared_ptr<Collision>>> collisions;
};
