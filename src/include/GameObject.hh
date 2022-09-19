#pragma once

#include <vector>

#include "DrawingComp.hh"
#include "Memory.hh"
#include "PositionComp.hh"

// Forward decl, see PhysicsComp.hh
class PhysicsComp;

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles. They can be drawn, though
  // they may not be visible (i.e triggers).

 public:
  DrawingCompSPtr getDrawingCompSPtr();

 protected:
  PositionCompSPtr positionComp;
  shared_ptr<PhysicsComp> physicsComp;
  DrawingCompSPtr drawingCompSPtr;
};

typedef shared_ptr<GameObject> GameObjectSPtr;
typedef std::vector<GameObjectSPtr> GameObjectSPtrCollection;
