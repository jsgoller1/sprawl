#pragma once

#include <vector>

#include "DrawingComp.hh"
#include "Memory.hh"
#include "PhysicsMgr.hh"
#include "PositionComp.hh"

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles. They can be drawn.
 public:
  DrawingCompSPtr getDrawingComp();

 private:
  PositionCompSPtr positionMgr;
  PhysicsMgrSPtr physicsMgr;
  DrawingCompSPtr drawingCompSPtr;
};

typedef shared_ptr<GameObject> GameObjectSPtr;
typedef std::vector<GameObjectSPtr> GameObjectSPtrCollection;
