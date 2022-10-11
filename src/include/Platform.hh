#pragma once

#include "CollisionDetectionComponent.hh"
#include "GameObject.hh"
#include "PhysicsComponent.hh"

class Platform : public GameObject {
  // Platforms are gravity-disabled surfaces with colliders; examples include
  // walls, floors, cielings, ground, etc.
 public:
  Platform(const shared_ptr<EntityName> entityName = nullptr,
           const shared_ptr<PositionComponent> positionComponent = nullptr,
           const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
           const shared_ptr<CollisionDetectionComponent>
               collisionDetectionComponent = nullptr,
           const shared_ptr<DrawingComponent> drawingComponent = nullptr)
      : GameObject(entityName, positionComponent, collisionDetectionComponent,
                   physicsComponent, drawingComponent) {}
};
