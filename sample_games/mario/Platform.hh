#pragma once

#include "CollisionComponent.hh"
#include "GameObject.hh"
#include "PhysicsComponent.hh"

class Platform : public GameObject {
  // Platforms are gravity-disabled surfaces with colliders; examples include
  // walls, floors, cielings, ground, etc.
 public:
  Platform(const EntityName& entityName, const std::shared_ptr<PositionComponent> positionComponent = nullptr,
           const std::shared_ptr<PhysicsComponent> physicsComponent = nullptr,
           const std::shared_ptr<CollisionComponent> collisionComponent = nullptr,
           const std::shared_ptr<GraphicsComponent2D> graphicsComponent2D = nullptr);
  virtual ~Platform() override;
};
