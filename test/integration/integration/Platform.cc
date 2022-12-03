#include "Platform.hh"

Platform::~Platform() = default;

Platform::Platform(const EntityName& entityName, const std::shared_ptr<PositionComponent> positionComponent,
                   const std::shared_ptr<RealisticPhysicsComponent> physicsComponent,
                   const std::shared_ptr<CollisionComponent> collisionComponent,
                   const std::shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(entityName, positionComponent, collisionComponent, physicsComponent, drawingComponent) {}
