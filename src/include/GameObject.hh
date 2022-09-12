#pragma once

#include <vector>

#include "Memory.hh"
#include "PhysicsMgr.hh"
#include "PositionMgr.hh"

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles

 private:
  PositionMgrSPtr positionMgr;
  PhysicsMgrSPtr physicsMgr;
};

typedef shared_ptr<GameObject> GameObjectSPtr;
typedef std::vector<GameObjectSPtr> GameObjectSPtrCollection;
