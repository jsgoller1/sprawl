#pragma once

#include "Math.hh"
#include "PhysicsTypes.hh"

// Forward decl
class PhysicsComponent;

/*
 * A Collision represents the fact that a collision occurred with a particular
 * object, and stores what type of collision it was.
 */

class Collision {
 public:
  shared_ptr<Identity> getIdentity() const;
  CollisionAxis getAxis() const;
  CollisionType getType() const;

 private:
  shared_ptr<Identity> identity;
  CollisionAxis axis;
  CollisionType type;
};

/*
 * A CollisionTestResult stores information other objects can use to determine
 * what to do after a collision test.
 */

class CollisionTestResult {
 public:
  bool collisionOccurred() const;
  shared_ptr<set<shared_ptr<Collision>>> collisions;
  shared_ptr<Vect2D> attemptedMove;
  shared_ptr<Vect2D> validMove;
};
