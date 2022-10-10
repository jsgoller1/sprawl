#pragma once

#include "CollisionDetectionComponent.hh"
#include "GameObject.hh"
#include "PhysicsComponent.hh"

class Platform : public GameObject {
  // Platforms are gravity-disabled surfaces with colliders; examples include
  // walls, floors, cielings, ground, etc.
 public:
  Platform(const shared_ptr<Identity> identity,
           const shared_ptr<PositionComponent> positionComponent,
           const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
           const shared_ptr<CollisionDetectionComponent>
               collisionDetectionComponent = nullptr,
           const shared_ptr<DrawingComponent> drawingComponent = nullptr)
      : GameObject(identity, positionComponent, physicsComponent,
                   collisionDetectionComponent, drawingComponent) {}
};
