#pragma once

#include "BoundingBox.hh"
#include "Memory.hh"
#include "PhysicsManager.hh"
#include "PositionComponent.hh"

// Forward decls
class PhysicsManager;
class GameObject;

class PhysicsComponent : public enable_shared_from_this<PhysicsComponent> {
  // Any GameObject can have a physics component; if it does, it registers
  // it with the global PhysicsManager.
 public:
  PhysicsComponent(const shared_ptr<PositionComponent> positionComponent,
                   const shared_ptr<BoundingBox> boundingBox = nullptr,
                   const bool collisionsSetting = false,
                   const bool gravitySetting = false);
  shared_ptr<PhysicsComponent> getptr();

  // Forwarding methods for PositionComponent
  void move(shared_ptr<Point> direction);
  shared_ptr<Point> getCenter();

  bool hasCollisions();
  void enableCollisions(const bool setting);
  bool hasGravity();
  void enableGravity(const bool setting);
  shared_ptr<BoundingBox> getBoundingBox();
  void setBoundingBox(const shared_ptr<BoundingBox> box);
  void setBoundingBox(const PositionUnit h, const PositionUnit w);
  void setVelocity(const shared_ptr<Point> velocity);
  shared_ptr<Point> getVelocity();
  void addVelocity(const shared_ptr<Point> velocity);

  bool predictMovementCollision();
  bool isColliding();

  shared_ptr<PhysicsManager> getManager();
  void setManager(const shared_ptr<PhysicsManager> manager);

  // TODO: Physics components should probably only talk to other physics
  // components; as such, when we detect collisions, the physics manager should
  // return a list of physics components, and then we return a list of
  // gameObjects to the caller

  shared_ptr<vector<shared_ptr<GameObject>>> getCollisionObjects();

 private:
  bool collisionsEnabled;
  bool gravityEnabled;
  shared_ptr<Point> velocity;
  shared_ptr<GameObject> parentGameObject;
  shared_ptr<PositionComponent> positionComponent;
  shared_ptr<BoundingBox> boundingBox;
  shared_ptr<PhysicsManager> manager;
};
