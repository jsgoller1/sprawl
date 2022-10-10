#pragma once

#include <vector>

#include "BoundingBox.hh"
#include "DrawingComponent.hh"
#include "Entity.hh"
#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"

class GameObject : public Entity {
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
  shared_ptr<CollisionDetectionComponent> getCollisionDetectionComponent() {
    return this->collisionDetectionComponent;
  }
  void setCollisionDetectionComponent(
      const shared_ptr<CollisionDetectionComponent>
          collisionDetectionComponent) {
    this->collisionDetectionComponent = collisionDetectionComponent;
  }

  // NOTE: GameObjectIDs should not be set except at object creation time;
  // eventually, we will have a manager for this to ensure uniqueness.
  shared_ptr<Identity> getIdentity() { return this->identity; }

  void inferBoundingBoxFromTexture();

 protected:
  // TODO: Do we not want anything other than derived objects calling this
  // constructor?
  GameObject(const shared_ptr<Identity> identity,
             const shared_ptr<PositionComponent> positionComponent,
             const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
             const shared_ptr<CollisionDetectionComponent>
                 collisionDetectionComponent = nullptr,
             const shared_ptr<DrawingComponent> drawingComponent = nullptr)
      : identity(identity),
        positionComponent(positionComponent),
        physicsComponent(physicsComponent),
        collisionDetectionComponent(collisionDetectionComponent),
        drawingComponent(drawingComponent) {}

 private:
  shared_ptr<DrawingComponent> drawingComponent;
  shared_ptr<PhysicsComponent> physicsComponent;
  shared_ptr<PositionComponent> positionComponent;
  shared_ptr<CollisionDetectionComponent> collisionDetectionComponent;
  shared_ptr<Identity> identity;

  virtual void setPhysicsComponent_impl(PhysicsComponent* const comp) override;
  virtual PhysicsComponent* getPhysicsComponent_impl() const override;
};
