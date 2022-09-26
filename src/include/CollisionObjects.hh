#pragma once
#include <algorithm>
#include <set>

#include "Memory.hh"
#include "PhysicsComp.hh"

class CollisionObjects {
 public:
  void add();
  void remove();
  bool contains();
  // TODO: This is bad an leaks implementation details (about the fact that
  // CollisionObjects are implemented with sets); we should support a begin()
  // and end() method instead.
  shared_ptr<std::set<shared_ptr<PhysicsComp>>> getAll() const {
    return this->objects;
  }

  shared_ptr<CollisionObjects> getMerged(
      shared_ptr<CollisionObjects> otherObjects);
  shared_ptr<CollisionObjects> getRemoved(
      shared_ptr<CollisionObjects> otherObjects);

 private:
  shared_ptr<std::set<shared_ptr<PhysicsComp>>> objects;
};

typedef std::pair<shared_ptr<Vect2D>, shared_ptr<Vect2D>> CollisionResult;

enum CollisionAxes { X_AND_Y, Y_ONLY, X_ONLY };
