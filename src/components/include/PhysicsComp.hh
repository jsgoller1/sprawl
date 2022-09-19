#pragma once

#include "BoundingBox.hh"
#include "GameObject.hh"
#include "Memory.hh"

class PhysicsComp {
  // Any GameObject can have a physics component; if it does, it registers
  // it with the global PhysicsMgr.
 public:
  void move();  // forward method for parent's move()

  // TODO: Physics components should probably only talk to other physics
  // components; as such, when we detect collisions, the physics manager should
  // return a list of physics components, and then we return a list of
  // gameObjects to the caller
  GameObjectSPtrCollection getCollisions();

 private:
  bool collisions_enabled;
  bool gravity_enabled;
  GameObjectSPtr parentGameObject;
  BoundingBox boundingBox;
};

typedef shared_ptr<PhysicsComp> PhysicsCompSPtr;
