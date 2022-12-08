#pragma once
#include <memory>
#include <vector>

#include "Entity.hh"

// Forward decls
class PositionComponent;
class CollisionComponent;
class PhysicsComponent;
class DrawingComponent;

class GameObject : public Entity {
  /*
   * GameObjects are Entities in the world that the player can interact with.
   */

 public:
  GameObject(const EntityName& entityName, const std::shared_ptr<PositionComponent> positionComponent = nullptr,
             const std::shared_ptr<CollisionComponent> collisionComponent = nullptr,
             const std::shared_ptr<PhysicsComponent> physicsComponent = nullptr,
             const std::shared_ptr<DrawingComponent> drawingComponent = nullptr);
  virtual ~GameObject();
  virtual DrawingComponent& getDrawingComponent() const;
  virtual PhysicsComponent& getPhysicsComponent() const;
  virtual PositionComponent& getPositionComponent() const;
  virtual CollisionComponent& getCollisionComponent() const;

  void inferBoundingBoxFromTexture();

 private:
  std::shared_ptr<PositionComponent> positionComponent;
  std::shared_ptr<PhysicsComponent> physicsComponent;
  std::shared_ptr<CollisionComponent> collisionComponent;
  std::shared_ptr<DrawingComponent> drawingComponent;
};
