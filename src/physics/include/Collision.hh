#pragma once

#include "Math.hh"
#include "Types.hh"

// Forward decl
class PhysicsComponent;

typedef std::pair<shared_ptr<Vect2D>, shared_ptr<Vect2D>> CollisionResult;

enum CollisionAxes { X_AND_Y, Y_ONLY, X_ONLY };

class Collision {
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

  shared_ptr<Collision> getMerged(shared_ptr<Collision> otherObjects);
  shared_ptr<Collision> getRemoved(shared_ptr<Collision> otherObjects);

 private:
  shared_ptr<std::set<shared_ptr<PhysicsComponent>>> objects;
};
