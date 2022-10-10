
#pragma once

#include "BoundingBox.hh"
#include "CollisionDetectionManager.hh"
#include "CollisionTestResult.hh"
#include "Component.hh"
#include "Math.hh"
#include "Memory.hh"

class CollisionDetectionComponent : public Component {
  /*
   * CollisionDetectionComponent handles all collision testing on behalf of
   * PhysicsComponent. It knows how to work with BoundingBoxes, and how to
   * determine if it is colliding with another CollisionDetectionComponent. It
   * doesn't know anything about what should happen as a result of a collision;
   * it is only for testing.
   */
 public:
  CollisionDetectionComponent(
      const shared_ptr<PositionComponent> positionComponent,
      const shared_ptr<BoundingBoxParams> boundingBoxParams,
      const bool collisionsEnabled = true)
      : positionComponent(positionComponent),
        boundingBoxParams(boundingBoxParams),
        collisionsEnabled(collisionsEnabled) {}
  shared_ptr<CollisionDetectionComponent> getptr();

  shared_ptr<PositionComponent> getPositionComponent() const {
    return this->positionComponent;
  }
  void setPositionComponent(
      const shared_ptr<PositionComponent> positionComponent) {
    this->positionComponent = positionComponent;
  }

  shared_ptr<BoundingBoxParams> getBoundingBoxParams() const {
    return this->boundingBoxParams;
  };
  void setBoundingBoxParams(const shared_ptr<BoundingBoxParams> params) {
    this->boundingBoxParams = params;
  };

  bool getCollisionsEnabled() const { return this->collisionsEnabled; }
  void setCollisionsEnabled(const bool setting) {
    this->collisionsEnabled = setting;
  }

  shared_ptr<BoundingBox> getBoundingBox() const;
  bool areColliding(const shared_ptr<CollisionDetectionComponent> comp) const;
  shared_ptr<CollisionTestResult> testCollisions(
      const shared_ptr<Vect2D> movement);

 private:
  bool collisionsEnabled;
  shared_ptr<BoundingBoxParams> boundingBoxParams;
  shared_ptr<PositionComponent> positionComponent;
  shared_ptr<CollisionDetectionManager> manager;

  shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>
  predictMovementCollision(const shared_ptr<Vect2D> movement);
  CollisionAxis determineCollisionAxis(
      const shared_ptr<CollisionDetectionComponent> target,
      const shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>
          xCollisions,
      const shared_ptr<set<shared_ptr<CollisionDetectionComponent>>>
          yCollisions);
};
