#pragma once

class ICollision {
 public:
  bool collisionTest(const ICollision& target) const;
  virtual void resolveCollision(ICollision& target) = 0;
};
