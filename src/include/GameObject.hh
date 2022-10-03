#pragma once

#include "DrawingComp.hh"
#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "PositionComp.hh"
#include "Types.hh"

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles. They can be drawn, though
  // they may not be visible (i.e triggers).

  // TODO: For now, GameObjects are an ABC because of derived classes
  // needing to return shared pointers to components and our use of
  // private methods returning raw pointers. Should we want this to become a
  // concrete class, we should move the pure virtual methods to a parent
  // GameObjectBase class,

 public:
  DrawingCompSPtr getDrawingComponent();

  shared_ptr<PhysicsComponent> getPhysicsComponent() {
    return this->getRawPhysicsComponent()->getptr();
  }

  GameObjectNameSPtr getName() { return this->name; }
  shared_ptr<PositionComp> getPositionComponent() { return this->positionComp; }

 protected:
  GameObject(const shared_ptr<Vect2D> center, const GameObjectNameSPtr name,
             const shared_ptr<PhysicsComponent> physicsComp = nullptr,
             const FilePathSPtr texturePath = nullptr,
             const DrawingCompSPtr drawingComp = nullptr);

  GameObject(const shared_ptr<Vect2D> center,
             const GameObjectNameSPtr name = nullptr,
             const FilePathSPtr texturePath = nullptr,
             const DrawingCompSPtr drawingComp = nullptr);

 private:
  virtual PhysicsComponent* getRawPhysicsComponent() = 0;

  void init(const shared_ptr<Vect2D> center, const GameObjectNameSPtr name,
            const shared_ptr<PhysicsComponent> physicsComp,
            const FilePathSPtr texturePath, const DrawingCompSPtr drawingComp);

  GameObjectNameSPtr name;
  shared_ptr<PositionComp> positionComp;
  DrawingCompSPtr drawingComp;
  shared_ptr<PhysicsComponent> physicsComp;
};

typedef shared_ptr<GameObject> GameObjectSPtr;
typedef std::vector<GameObjectSPtr> GameObjectSPtrCollection;
