#pragma once

#include "BoundingBox.hh"
#include "GameObject.hh"
#include "Memory.hh"
#include "PhysicsMgr.hh"
#include "PositionComp.hh"

// Forward decls
class PhysicsMgr;
class GameObject;

class PhysicsComp : public enable_shared_from_this<PhysicsComp> {
  // Any GameObject can have a physics component; if it does, it registers
  // it with the global PhysicsMgr.
 public:
  PhysicsComp(const PositionCompSPtr positionComp,
              const BoundingBoxSPtr boundingBox = nullptr,
              const bool collisionsSetting = false,
              const bool gravitySetting = false);
  shared_ptr<PhysicsComp> getptr();

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

  bool predictMovementCollision();
  bool isColliding();

  shared_ptr<PhysicsMgr> getManager();
  void setManager(const shared_ptr<PhysicsMgr> manager);

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
  shared_ptr<GameObject> parentGameObject;
  PositionCompSPtr positionComp;
  BoundingBoxSPtr boundingBox;
  shared_ptr<PhysicsMgr> manager;
};
