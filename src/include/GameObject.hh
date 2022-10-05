#pragma once

#include "CollisionDetectionComponent.hh"
#include "DrawingComp.hh"
#include "Logger.hh"
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
             const DrawingCompSPtr drawingComp = nullptr) {
    this->init(center, name, physicsComp, drawingComp, texturePath, nullptr,
               nullptr);
  }

  GameObject(const shared_ptr<Vect2D> center,
             const GameObjectNameSPtr name = nullptr,
             const FilePathSPtr texturePath = nullptr,
             const DrawingCompSPtr drawingComp = nullptr) {
    this->init(center, name, nullptr, drawingComp, texturePath, nullptr,
               nullptr);
  }

 private:
  virtual PhysicsComponent* getRawPhysicsComponent() = 0;

  void init(
      const shared_ptr<Vect2D> center, const GameObjectNameSPtr name,
      const shared_ptr<PhysicsComponent> physicsComp,
      const DrawingCompSPtr drawingComp, const FilePathSPtr texturePath,
      const shared_ptr<CollisionDetectionComponent> collisionDetectionComponent,
      const shared_ptr<BoundingBoxParams> boundingBoxParams);

  GameObjectNameSPtr name;
  shared_ptr<PositionComp> positionComp;
  DrawingCompSPtr drawingComp;
  shared_ptr<PhysicsComponent> physicsComp;
  shared_ptr<CollisionDetectionComponent> collisionDetectionComponent;
};

typedef shared_ptr<GameObject> GameObjectSPtr;
typedef std::vector<GameObjectSPtr> GameObjectSPtrCollection;
