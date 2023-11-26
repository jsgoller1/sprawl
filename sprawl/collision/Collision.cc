#include "Collision.hh"

Collision::Collision(const std::weak_ptr<Actor> source, const std::weak_ptr<Actor> target,
                     const Vect2D& originalPosition, const Vect2D& attemptedMove, const Vect2D& finalPosition,
                     const CollisionAxis collisionAxis)
    : _source(source),
      _target(target),
      _originalPosition(originalPosition),
      _attemptedMove(attemptedMove),
      _finalPosition(finalPosition),
      _collisionAxis(collisionAxis){};

std::weak_ptr<Actor> Collision::source() const { return this->_source; }
std::weak_ptr<Actor> Collision::target() const { return this->_target; }
Vect2D Collision::originalPosition() const { return this->_originalPosition; }
Vect2D Collision::attemptedMove() const { return this->_attemptedMove; }
Vect2D Collision::finalPosition() const { return this->_finalPosition; }
CollisionAxis Collision::collisionAxis() const { return this->_collisionAxis; }
