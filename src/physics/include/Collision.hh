#pragma once

#include "Math.hh"
#include "Types.hh"

// Forward decl
class PhysicsComponent;

enum CollisionAxes { X_AND_Y, Y_ONLY, X_ONLY };
enum CollisionType { PSEUDO, ELASTIC };
class ElasticCollisionResult {};

class CollisionSet {
  /*
   * A CollisionSet represents the set of objects that a moving object has
   * collided with. "Set" here refers to the mathematical sense of a set, not
   * std::set().
   */
 public:
  void add();
  void remove();
  bool contains();
  // TODO: This is bad an leaks implementation details (about the fact that
  // CollidingPhysicsComponents are implemented with sets); we should support a
  // begin() and end() method instead.
  shared_ptr<std::set<shared_ptr<PhysicsComponent>>> getAll() const {
    return this->objects;
  }

  shared_ptr<CollisionSet> setwiseAnd(shared_ptr<CollisionSet> otherObjects);
  shared_ptr<CollisionSet> setwiseComplement(
      shared_ptr<CollisionSet> otherObjects);

 private:
  shared_ptr<std::set<shared_ptr<PhysicsComponent>>> objects;
};
