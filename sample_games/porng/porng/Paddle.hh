#pragma once

#include <memory>

#include "GameObject.hh"

// Forward decls
class CollisionComponent;
class DrawingComponent;
class PositionComponent;
class SimplePhysicsComponent;
class Vect2D;

class Paddle : public GameObject {
 public:
  Paddle(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent = nullptr,
         const std::shared_ptr<SimplePhysicsComponent> _physicsComponent = nullptr,
         const std::shared_ptr<CollisionComponent> collisionComponent = nullptr,
         const std::shared_ptr<DrawingComponent> drawingComponent = nullptr);
  ~Paddle() override;

  void move(const Vect2D& distance);
  // TODO: This technique of reconciling smart pointers with the covariant return rule wound up being an anti-pattern
  // and is slated for removal. It's here at present merely to satisfy concretizing this class, but won't do anything.
  // std::shared_ptr<PhysicsComponent> getPhysicsComponent() const;
  // void setPhysicsComponent(const std::shared_ptr<PhysicsComponent> physicsComponent);

 private:
  std::shared_ptr<SimplePhysicsComponent> _physicsComponent;
};
