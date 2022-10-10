#pragma once

#include "Memory.hh"
#include "Types.hh"

// Forward decl
class CollisionDetectionComponent;

class CollisionDetectionManager {
  /*
   * CollisionDetectionManager fulfills the Manager role within the ECS for
   * CollisionComponents.
   */
 public:
  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>
  getCollisionCandidates(
      const shared_ptr<CollisionDetectionComponent> source) const;

 private:
  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>> managedComponents;
};
