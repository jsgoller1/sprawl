#pragma once

#include "Identity.hh"
#include "Math.hh"
#include "PhysicsTypes.hh"

class Collision {
  /*
   * Collision keeps track of relevant information about when one object
   * collides with another. When testing a batch of objects against the same
   * source, this results in some wasteful / redundant information (i.e. a
   * collection<Collision> where each member has the same source, original
   * position, and attempted move), but results in simpler code.
   */
 public:
  Collision(const std::shared_ptr<Identity> source, std::shared_ptr<Identity> target, const Vect2D& originalPosition,
            const Vect2D& attemptedMove, const Vect2D& finalPosition, const CollisionAxis collisionAxis);

  std::shared_ptr<Identity> source() const;
  std::shared_ptr<Identity> target() const;
  Vect2D originalPosition() const;
  Vect2D attemptedMove() const;
  Vect2D finalPosition() const;
  CollisionAxis collisionAxis() const;

 private:
  std::shared_ptr<Identity> _source;
  std::shared_ptr<Identity> _target;
  Vect2D _originalPosition;
  Vect2D _attemptedMove;
  Vect2D _finalPosition;
  CollisionAxis _collisionAxis;
};
