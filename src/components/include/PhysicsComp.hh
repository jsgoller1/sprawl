#pragma once

#include "BoundingBox.hh"
#include "GameObject.hh"
#include "Memory.hh"
#include "PhysicsMgr.hh"
#include "PositionComp.hh"

// Forward decls
class PhysicsMgr;
class GameObject;

class PhysicsComp {
  // Any GameObject can have a physics component; if it does, it registers
  // it with the global PhysicsMgr.
 public:
  PhysicsComp(const PositionCompSPtr positionComp,
              const BoundingBoxSPtr boundingBox = nullptr,
              const bool collisionsSetting = false,
              const bool gravitySetting = false);
  void move();  // forward method for parent's move()
  bool hasCollisions();
  void setCollisions(const bool setting);
  bool hasGravity();
  void setGravity(const bool setting);
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
  shared_ptr<GameObject> parentGameObject;
  PositionCompSPtr positionComp;
  BoundingBoxSPtr boundingBox;
  shared_ptr<PhysicsMgr> manager;
};
