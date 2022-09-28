#pragma once

#include <vector>

#include "DrawingComp.hh"
#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "PositionComp.hh"

// Forward decls
class PhysicsComponent;  // see PhysicsComponent.hh

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles. They can be drawn, though
  // they may not be visible (i.e triggers).

 public:
  DrawingCompSPtr getDrawingComponent();
  shared_ptr<PhysicsComponent> getPhysicsComponent();
  void inferBoundingBoxFromTexture();

 protected:
  GameObject(const shared_ptr<Vect2D> center,
             const GameObjectNameSPtr name = nullptr,
             const shared_ptr<PhysicsComponent> physicsComp = nullptr,
             const FilePathSPtr texturePath = nullptr,
             const DrawingCompSPtr drawingComp = nullptr);

  GameObjectNameSPtr name;
  shared_ptr<PositionComp> positionComp;
  DrawingCompSPtr drawingComp;
  shared_ptr<PhysicsComponent> physicsComp;
};

typedef shared_ptr<GameObject> GameObjectSPtr;
typedef std::vector<GameObjectSPtr> GameObjectSPtrCollection;
