#include "Paddle.hh"

Paddle::~Paddle() = default;

Paddle::Paddle(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent,
               const std::shared_ptr<CollisionComponent> collisionComponent,
               const std::shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(entityName, positionComponent, collisionComponent, nullptr, drawingComponent) {}
