
#pragma once

#include "BoundingBox.hh"
#include "CollisionTestResult.hh"
#include "Math.hh"
#include "Memory.hh"

/*
 * CollisionDetectionComponent handles all collision testing on behalf of
 * PhysicsComponent. It knows how to work with BoundingBoxes, and how to
 * determine if it is colliding with another CollisionDetectionComponent. It
 * doesn't know anything about what should happen as a result of a collision; it
 * is only for testing.
 */

class CollisionDetectionComponent {
 public:
  CollisionDetectionComponent(
      const shared_ptr<PositionComponent> positionComponent,
      const shared_ptr<BoundingBoxParams> boundingBoxParams,
      const bool collisionsEnabled = true)
      : positionComponent(positionComponent),
        boundingBoxParams(boundingBoxParams),
        collisionsEnabled(collisionsEnabled) {}

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
  bool detectCollision() const;
  shared_ptr<CollisionTestResult> predictMovementCollision(
      const shared_ptr<Vect2D> movement);

 private:
  bool collisionsEnabled;
  shared_ptr<BoundingBoxParams> boundingBoxParams;
  shared_ptr<PositionComponent> positionComponent;
};
