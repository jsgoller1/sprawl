#pragma once

#include "Math.hh"
#include "PhysicsTypes.hh"

// Fwd decls
class Actor;

class Collision {
  /*
   * Collision keeps track of relevant information about when one object
   * collides with another. When testing a batch of objects against the same
   * source, this results in some wasteful / redundant information (i.e. a
   * collection<Collision> where each member has the same source, original
   * position, and attempted move), but results in simpler code.
   */
 public:
  Collision(const std::weak_ptr<Actor> source, std::weak_ptr<Actor> target, const Vect2D& originalPosition,
            const Vect2D& attemptedMove, const Vect2D& finalPosition, const CollisionAxis collisionAxis);

  std::weak_ptr<Actor> source() const;
  std::weak_ptr<Actor> target() const;
  Vect2D originalPosition() const;
  Vect2D attemptedMove() const;
  Vect2D finalPosition() const;
  CollisionAxis collisionAxis() const;

 private:
  std::weak_ptr<Actor> _source;
  std::weak_ptr<Actor> _target;
  Vect2D _originalPosition;
  Vect2D _attemptedMove;
  Vect2D _finalPosition;
  CollisionAxis _collisionAxis;
};
