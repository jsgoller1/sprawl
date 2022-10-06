#pragma once

#include "GameObject.hh"
#include "PhysicsComponent.hh"

class Platform : public GameObject {
  // Platforms are gravity-disabled surfaces with colliders; examples include
  // walls, floors, cielings, ground, etc.
 public:
  Platform(const shared_ptr<GameObjectID> gameObjectID,
           const shared_ptr<PositionComponent> positionComponent,
           const shared_ptr<PhysicsComponent> physicsComponent = nullptr,
           const shared_ptr<DrawingComponent> drawingComponent = nullptr)
      : GameObject(gameObjectID, positionComponent, physicsComponent,
                   drawingComponent) {}
};
