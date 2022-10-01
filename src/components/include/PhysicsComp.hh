#pragma once

#include <vector>

#include "BoundingBox.hh"
#include "Component.hh"
#include "GameObject.hh"
#include "Memory.hh"
#include "PositionComp.hh"

// Forward decls
class GameObject;
class PhysicsMgr;

class PhysicsComp : public Component<PhysicsComp> {
  // Any GameObject can have a physics component; if it does, it registers
  // it with the global PhysicsMgr.
 public:
  PhysicsComp(const shared_ptr<const Identity> parentIdentity,
              const PositionCompSPtr positionComp,
              const BoundingBoxSPtr boundingBox = nullptr,
              const bool collisionsSetting = false,
              const bool gravitySetting = false);

  // Forwarding methods for PositionComp
  void move(PointSPtr direction);
  PointSPtr getCenter();

  bool hasCollisions();
  void enableCollisions(const bool setting);
  bool hasGravity();
  void enableGravity(const bool setting);
  BoundingBoxSPtr getBoundingBox();
  void setBoundingBox(const BoundingBoxSPtr box);
  void setBoundingBox(const PositionUnit h, const PositionUnit w);
  void setVelocity(const PointSPtr velocity);
  PointSPtr getVelocity();
  void addVelocity(const PointSPtr velocity);

  bool predictMovementCollision();

  // TODO: Physics components should probably only talk to other physics
  // components; as such, when we detect collisions, the physics manager should
  // return a list of physics components, and then we return a list of
  // gameObjects to the caller

  // TODO: Can't use GameObjectSPtrCollection due to circular include/fwd decl
  shared_ptr<vector<shared_ptr<GameObject>>> getCollisionObjects();

 private:
  bool collisionsEnabled;
  bool gravityEnabled;
  PointSPtr velocity;
  PositionCompSPtr positionComp;
  BoundingBoxSPtr boundingBox;
};
