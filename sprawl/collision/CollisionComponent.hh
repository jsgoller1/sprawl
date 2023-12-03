
#pragma once

#include <set>
#include <unordered_set>
#include <vector>

#include "BoundingBox.hh"
#include "Collision.hh"
#include "Component.hh"
#include "Math.hh"

static constexpr char COLLISION_COMPONENT_NAME[] = "CollisionComponent";

// Forward decl
class Actor;
class CollisionManager;
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
  CollisionComponent(const PositionUnit height = 0.0, const PositionUnit width = 0.0,
                     const bool collisionsEnabled = false);
  ~CollisionComponent() override;

  std::string toString() const override;
  void managerRegister() override;
  void managerUnregister() override;

  bool collisionsEnabled() const;
  void collisionsEnabled(const bool setting);
  PositionUnit height() const;
  void height(const PositionUnit val);
  PositionUnit width() const;
  void width(const PositionUnit val);

  BoundingBox boundingBox(const Vect2D& offset = Vect2D::zero()) const;

 private:
  friend CollisionManager;
  bool isColliding(const Vect2D& target, const Vect2D& sourceOffset) const;
  bool isColliding(const Line& target, const Vect2D& sourceOffset) const;
  bool isColliding(const CollisionComponent& target, const Vect2D& sourceOffset) const;

  PositionUnit _height;
  PositionUnit _width;
  bool _collisionsEnabled;
};
