/*
 * CollisionDetectionComponent handles all collision testing on behalf of
 * PhysicsComponent. It knows how to work with BoundingBoxes, and how to
 * determine if it is colliding with another CollisionDetectionComponent. It
 * doesn't know anything about what should happen as a result of a collision; it
 * is only for testing.
 */

#include "BoundingBox.hh"
#include "Collision.hh"
#include "Math.hh"
#include "Memory.hh"

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

  bool isColliding(const shared_ptr<CollisionDetectionComponent> comp) const;
  shared_ptr<BoundingBox> getBoundingBox() const;
  bool checkCollision(const shared_ptr<CollisionDetectionComponent> comp) const;

 private:
  bool collisionsEnabled;
  shared_ptr<BoundingBoxParams> boundingBoxParams;
  shared_ptr<PositionComponent> positionComponent;
};
