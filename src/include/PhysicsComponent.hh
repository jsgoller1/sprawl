#pragma once

#include "BoundingBox.hh"
#include "GameObject.hh"
#include "Memory.hh"

class PhysicsComponent {
  // Any GameObject can have a physics component; if it does, it registers
  // it with the global PhysicsManager.
 public:
  void move();  // forward method for parent's move()
  shared_ptr<GameObjectCollection> getCollisions();

 private:
  bool collisions_enabled;
  bool gravity_enabled;
  GameObject parentGameObject;
  BoundingBox boundingBox;
};
