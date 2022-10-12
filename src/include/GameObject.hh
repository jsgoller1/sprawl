#pragma once

#include <vector>

#include "BoundingBox.hh"
#include "DrawingComponent.hh"
#include "Entity.hh"
#include "Memory.hh"
#include "PhysicsComponent.hh"
#include "PositionComponent.hh"

class GameObject : public Entity {
  /*
   * GameObjects are Entities in the world that the player can interact with.
   */

 public:
  GameObject(const shared_ptr<EntityName> entityName = nullptr,
             const shared_ptr<PositionComponent> positionComponent = nullptr,
             const shared_ptr<CollisionComponent> collisionComponent = nullptr,
             const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
             const shared_ptr<DrawingComponent> drawingComponent = nullptr);

  shared_ptr<DrawingComponent> getDrawingComponent() const {
    return this->drawingComponent;
  }
  void setDrawingComponent(
      const shared_ptr<DrawingComponent> drawingComponent) {
    this->drawingComponent = drawingComponent;
  }
  shared_ptr<PhysicsComponent> getPhysicsComponent() const {
    return this->getPhysicsComponent_impl()->getptr();
  }
  void setPhysicsComponent(
      const shared_ptr<PhysicsComponent> physicsComponent) {
    this->setPhysicsComponent_impl(physicsComponent.get());
  }
  shared_ptr<PositionComponent> getPositionComponent() const {
    return this->positionComponent;
  }
  void setPositionComponent(
      const shared_ptr<PositionComponent> positionComponent) {
    this->positionComponent = positionComponent;
  }
  shared_ptr<CollisionComponent> getCollisionComponent() {
    return this->collisionComponent;
  }
  void setCollisionComponent(
      const shared_ptr<CollisionComponent> collisionComponent) {
    this->collisionComponent = collisionComponent;
  }

  void inferBoundingBoxFromTexture();

 private:
  shared_ptr<PositionComponent> positionComponent;
  shared_ptr<PhysicsComponent> physicsComponent;
  shared_ptr<CollisionComponent> collisionComponent;
  shared_ptr<DrawingComponent> drawingComponent;

  // NOTE: This is a technique we use to allow for covariant returns
  // with smart pointers; unfortunately, it doesn't also work for
  // setters because of restrictions on parameters that don't apply to
  // return types. We might be able to get a complicated solution mixing
  // inheiritance and templates, but we'll settle with some unfortunate name
  // hiding for now.
  // https://www.fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance/

  virtual void setPhysicsComponent_impl(PhysicsComponent* const comp);
  virtual PhysicsComponent* getPhysicsComponent_impl() const;
};
