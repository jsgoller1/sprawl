#pragma once

#include <vector>

#include "DrawingComp.hh"
#include "Memory.hh"
#include "PhysicsComp.hh"
#include "PositionComp.hh"

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles. They can be drawn, though
  // they may not be visible (i.e triggers).

 public:
  DrawingCompSPtr getDrawingCompSPtr();

 protected:
  GameObject(const PointSPtr center, const GameObjectNameSPtr name = nullptr,
             const PhysicsCompSPtr physicsComp = nullptr,
             const FilePathSPtr texturePath = nullptr,
             const DrawingCompSPtr drawingComp = nullptr);

  GameObjectNameSPtr name;
  PositionCompSPtr positionComp;
  DrawingCompSPtr drawingComp;
  PhysicsCompSPtr physicsComp;
};

typedef shared_ptr<GameObject> GameObjectSPtr;
typedef std::vector<GameObjectSPtr> GameObjectSPtrCollection;
