#include "Ball.hh"

#include "SimplePhysicsComponent.hh"

Ball::Ball(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent,
           const std::shared_ptr<SimplePhysicsComponent> physicsComponent,
           const std::shared_ptr<CollisionComponent> collisionComponent,
           const std::shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(entityName, positionComponent, collisionComponent, physicsComponent, drawingComponent) {}
Ball::~Ball() = default;
