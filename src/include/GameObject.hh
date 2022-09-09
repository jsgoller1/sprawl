#pragma once

#include <vector>

#include "Memory.hh"
#include "PhysicsManager.hh"
#include "PositionManager.hh"

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles

 private:
  shared_ptr<PositionManager> positionManager;
  shared_ptr<PhysicsManager> physicsManager;
};

typedef shared_ptr<GameObject> GameObjectPS;
typedef std::vector<GameObjectPS> GameObjectPSCollection;
