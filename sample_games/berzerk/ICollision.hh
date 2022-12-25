#pragma once

class ICollision {
 public:
  virtual ~ICollision();
  bool collisionTest(const ICollision& target) const;
  virtual void resolveCollision(ICollision& target) = 0;
};
