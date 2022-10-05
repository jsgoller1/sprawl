#pragma once

#include <vector>

#include "DrawingComponent.hh"
#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"

class GameObject {
  // GameObjects are anything interactive in the world;
  // items, characters, vehicles. They can be drawn, though
  // they may not be visible (i.e triggers).

 public:
  shared_ptr<DrawingComponent> getDrawingComponent() const {
    return this->drawingComponent;
  }
  void setDrawingComponent(
      const shared_ptr<DrawingComponent> drawingComponent) {
    this->drawingComponent = drawingComponent;
  }
  shared_ptr<PhysicsComponent> getPhysicsComponent() const {
    return this->physicsComponent;
  }
  void setPhysicsComponent(
      const shared_ptr<PhysicsComponent> physicsComponent) {}
  shared_ptr<PositionComponent> getPositionComponent() const {
    return this->positionComponent;
  }
  void setPositionComponent(
      const shared_ptr<PositionComponent> positionComponent) {
    this->positionComponent = positionComponent;
  }

  // NOTE: GameObjectIDs should not be set except at object creation time;
  // eventually, we will have a manager for this to ensure uniqueness.
  shared_ptr<const GameObjectID> getGameObjectID() {
    return this->gameObjectID;
  }

  void inferBoundingBoxFromTexture();

 protected:
  // TODO: Do we not want anything other than derived objects calling this
  // constructor
  GameObject(const shared_ptr<GameObjectID> gameObjectID,
             const shared_ptr<PositionComponent> positionComponent,
             const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
             const shared_ptr<DrawingComponent> drawingComponent = nullptr)
      : gameObjectID(gameObjectID),
        positionComponent(positionComponent),
        physicsComponent(physicsComponent),
        drawingComponent(drawingComponent) {}

 private:
  shared_ptr<DrawingComponent> drawingComponent;
  shared_ptr<PhysicsComponent> physicsComponent;
  shared_ptr<PositionComponent> positionComponent;
  shared_ptr<const GameObjectID> gameObjectID;
};
