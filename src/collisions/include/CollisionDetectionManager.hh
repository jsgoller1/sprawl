#pragma once

#include "CollisionDetectionComponent.hh"
#include "EntityManager.hh"
#include "Memory.hh"
#include "Types.hh"

class CollisionDetectionManager {
  /*
   * CollisionDetectionManager fulfills the Manager role within the ECS for
   * CollisionComponents.
   */
 public:
  void manageComponent(const shared_ptr<CollisionDetectionComponent> component);
  void unmanageComponent(
      const shared_ptr<CollisionDetectionComponent> component);

  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>
  getCollisionCandidates(
      const shared_ptr<CollisionDetectionComponent> source) const;

 private:
  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>> managedComponents;
};
