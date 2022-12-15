#include "Paddle.hh"

#include "SimplePhysicsComponent.hh"

Paddle::Paddle(const EntityName entityName, const std::shared_ptr<PositionComponent> positionComponent,
               const std::shared_ptr<SimplePhysicsComponent> physicsComponent,
               const std::shared_ptr<CollisionComponent> collisionComponent,
               const std::shared_ptr<DrawingComponent> drawingComponent)
    : GameObject(entityName, positionComponent, collisionComponent, physicsComponent, drawingComponent) {}

Paddle::~Paddle() = default;

void Paddle::move(const Vect2D& move) { (void)move; }
