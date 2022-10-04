
#include "BoundingBox.hh"
#include "Collision.hh"
#include "Math.hh"
#include "Memory.hh"

class CollisionComponent {
 public:
  CollisionComponent(const shared_ptr<BoundingBoxParams> boundingBoxParams,
                     const shared_ptr<PositionComp> positionComp)
      : boundingBoxParams(boundingBoxParams),
        positionComp(positionComp),
        collisionsEnabled(collisionsEnabled) {}

  shared_ptr<BoundingBox> getBoundingBox() const;
  bool checkCollision(const shared_ptr<CollisionComponent> comp) const;
  shared_ptr<Collision> getCollision();
  shared_ptr<CollisionResult> resolveElasticCollision(
      shared_ptr<PhysicsComponent> collisionTarget, const CollisionAxes axes,
      const bool applyResultToUs, const bool applyResultToThem);

  bool getCollisionsEnabled() const { return this->collisionsEnabled; }
  void setCollisionsEnabled(const bool setting) {
    this->collisionsEnabled = setting;
  }
  shared_ptr<BoundingBoxParams> getBoundingBoxParams() const {
    return this->boundingBoxParams;
  };
  void setBoundingBoxParams(const shared_ptr<BoundingBoxParams> params) {
    this->boundingBoxParams = params;
  };

  bool isColliding() const;
  bool checkCollision(const shared_ptr<CollisionComponent> comp) const;

 private:
  bool collisionsEnabled;
  shared_ptr<BoundingBoxParams> boundingBoxParams;
  shared_ptr<PositionComp> positionComp;
};
