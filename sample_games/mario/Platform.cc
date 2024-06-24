#include "Platform.hh"

Platform::~Platform() = default;

Platform::Platform(const EntityName& entityName, const std::shared_ptr<PositionComponent> positionComponent,
                   const std::shared_ptr<PhysicsComponent> physicsComponent,
                   const std::shared_ptr<CollisionComponent> collisionComponent,
                   const std::shared_ptr<GraphicsComponent2D> graphicsComponent2D)
    : GameObject(entityName, positionComponent, collisionComponent, physicsComponent, graphicsComponent2D) {}
