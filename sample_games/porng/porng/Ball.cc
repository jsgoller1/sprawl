#include "Ball.hh"

Ball::~Ball() = default;

Ball::Ball(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent,
           const std::shared_ptr<CollisionComponent> collisionComponent,
           const std::shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(entityName, positionComponent, collisionComponent, nullptr, drawingComponent) {}
