
#pragma once

#include "BoundingBox.hh"
#include "CollisionTestResult.hh"
#include "Component.hh"
#include "Math.hh"
#include "Memory.hh"

// Forward decl
class CollisionDetectionManager;

class CollisionComponent : public Component {
  /*
   * CollisionComponent handles all collision testing on behalf of
   * PhysicsComponent. It knows how to work with BoundingBoxes, and how to
   * determine if it is colliding with another CollisionComponent. It
   * doesn't know anything about what should happen as a result of a collision;
   * it is only for testing.
   */
 public:
  CollisionComponent(
      const shared_ptr<Identity> ownerIdentity,
      const shared_ptr<PositionComponent> positionComponent = nullptr,
      const shared_ptr<BoundingBoxParams> boundingBoxParams = nullptr,
      const bool collisionsEnabled = true);

  shared_ptr<CollisionComponent> getptr();

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
  bool areColliding(const shared_ptr<CollisionComponent> comp) const;
  shared_ptr<CollisionTestResult> testCollisions(
      const shared_ptr<Vect2D> movement,
      const shared_ptr<set<shared_ptr<CollisionComponent>>>
          collisionCandidates);

 private:
  bool collisionsEnabled;
  shared_ptr<BoundingBoxParams> boundingBoxParams;
  shared_ptr<PositionComponent> positionComponent;

  shared_ptr<set<shared_ptr<CollisionComponent>>> predictMovementCollision(
      const shared_ptr<Vect2D> movement,
      const shared_ptr<set<shared_ptr<CollisionComponent>>>
          collisionCandidates);
  CollisionAxis determineCollisionAxis(
      const shared_ptr<CollisionComponent> target,
      const shared_ptr<set<shared_ptr<CollisionComponent>>> xCollisions,
      const shared_ptr<set<shared_ptr<CollisionComponent>>> yCollisions);
};

CollisionAxis determineCollisionAxis(
    const shared_ptr<CollisionComponent> target,
    const shared_ptr<set<shared_ptr<CollisionComponent>>> xCollisions,
    const shared_ptr<set<shared_ptr<CollisionComponent>>> yCollisions);
