#pragma once

#include "CollisionComponent.hh"
#include "GameObject.hh"
#include "RealisticPhysicsComponent.hh"

class Platform : public GameObject {
  // Platforms are gravity-disabled surfaces with colliders; examples include
  // walls, floors, cielings, ground, etc.
 public:
  Platform(const EntityName& entityName, const std::shared_ptr<PositionComponent> positionComponent = nullptr,
           const std::shared_ptr<RealisticPhysicsComponent> physicsComponent = nullptr,
           const std::shared_ptr<CollisionComponent> collisionComponent = nullptr,
           const std::shared_ptr<DrawingComponent> drawingComponent = nullptr);
  virtual ~Platform() override;

  RealisticPhysicsComponent* getPhysicsComponent() const override;

 private:
  std::shared_ptr<RealisticPhysicsComponent> physicsComponent;
};
