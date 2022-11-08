
#pragma once

#include <set>
#include <vector>

#include "BoundingBox.hh"
#include "Collision.hh"
#include "Component.hh"
#include "Math.hh"

// Forward decl
class CollisionDetectionManager;
struct SortFnObject;

class CollisionComponent : public Component {
  /*
   * CollisionComponent handles all collision testing. It knows how to work with
   * BoundingBoxes, and how to determine if it is colliding with another
   * CollisionComponent. It doesn't know anything about what should happen as a
   * result of a collision; it is only for testing.
   *
   * NOTE: this is a relatively small class at the moment that does very little
   * beyond forwarding collision testing to BoundingBox. However, we should not
   * try to fold it into PhysicsComponent because:
   * 1) We will probably have other bounding volumes in the future than boxes
   * 2) We don't want collisions to be tightly coupled with physics; they are
   *    useful for other non-physical things as well such as line-of-sight
   *    tests, triggers, etc.
   */
 public:
  CollisionComponent(const std::shared_ptr<Identity> ownerIdentity,
                     const std::shared_ptr<PositionComponent> positionComponent, const PositionUnit height = 0.0,
                     const PositionUnit width = 0.0, const bool collisionsEnabled = false);

  std::shared_ptr<CollisionComponent> getptr();
  std::shared_ptr<PositionComponent> positionComponent() const;
  void positionComponent(const std::shared_ptr<PositionComponent> positionComponent);

  bool collisionsEnabled() const;
  void collisionsEnabled(const bool setting);
  PositionUnit height() const;
  void height(const PositionUnit val);
  PositionUnit width() const;
  void width(const PositionUnit val);

  BoundingBox boundingBox(const Vect2D& offset = Vect2D::zero()) const;
  std::shared_ptr<std::vector<Collision>> predictMovementCollisions(
      Vect2D positionDelta,
      const std::shared_ptr<std::set<std::shared_ptr<CollisionComponent>>> collisionComponents) const;
  bool isColliding(const Vect2D& target, const Vect2D& sourceOffset) const;
  bool isColliding(const Line& target, const Vect2D& sourceOffset) const;
  bool isColliding(const CollisionComponent& target, const Vect2D& sourceOffset) const;

  CollisionAxis determineCollisionAxis(const Vect2D& sourceMovement, const CollisionComponent& target) const;

  Vect2D determineFinalPosition(const Vect2D& sourcePosition, const Vect2D& positionDelta,
                                const CollisionComponent& target, const CollisionAxis collisionAxis) const;

 private:
  std::shared_ptr<PositionComponent> _positionComponent;
  PositionUnit _height;
  PositionUnit _width;
  bool _collisionsEnabled;
};
