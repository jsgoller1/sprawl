#pragma once

#include "ComponentManager.hh"
#include "PhysicsTypes.hh"
#include "Singleton.hh"

// Forward decls
class Collision;
class CollisionComponent;
class Line;
class Vect2D;

class CollisionManager : public ComponentManager, public Singleton<CollisionManager> {
 public:
  void gameLoopUpdate(const time_ms duration) override;

  // CollisionAxis determineCollisionAxis(const Vect2D& sourceMovement, const CollisionComponent& target) const;

  // Vect2D determineFinalPosition(const Vect2D& sourcePosition, const Vect2D& positionDelta,
  //                              const CollisionComponent& target, const CollisionAxis collisionAxis) const;

  // void predictMovementCollisions(const Vect2D& positionDelta,
  //                               std::unordered_set<std::shared_ptr<Actor>>& collisionCandidates,
  //                               std::vector<Collision>& collisions) const;

 private:
  friend Singleton<CollisionManager>;
  CollisionManager() = default;
  CollisionManager(const CollisionManager&) = delete;
  CollisionManager& operator=(const CollisionManager&) = delete;
};
