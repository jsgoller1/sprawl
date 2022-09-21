#pragma once

#include <vector>

#include "DrawingComp.hh"
#include "Memory.hh"
#include "PhysicsComp.hh"
#include "PositionComp.hh"

// Forward decls
class PhysicsComp;  // see PhysicsComp.hh

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles. They can be drawn, though
  // they may not be visible (i.e triggers).

 public:
  DrawingCompSPtr getDrawingComponent();
  shared_ptr<PhysicsComp> getPhysicsComponent();
  void inferBoundingBoxFromTexture();

 protected:
  GameObject(const PointSPtr center, const GameObjectNameSPtr name = nullptr,
             const shared_ptr<PhysicsComp> physicsComp = nullptr,
             const FilePathSPtr texturePath = nullptr,
             const DrawingCompSPtr drawingComp = nullptr);

  GameObjectNameSPtr name;
  PositionCompSPtr positionComp;
  DrawingCompSPtr drawingComp;
  shared_ptr<PhysicsComp> physicsComp;
};

typedef shared_ptr<GameObject> GameObjectSPtr;
typedef std::vector<GameObjectSPtr> GameObjectSPtrCollection;
