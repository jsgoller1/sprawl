#pragma once

#include "ShootingProxy.hh"

// Fwd decls
class Wall;
class Direction;
class Vect2D;  // TODO: Placeholder until we decide what type of collection class to use
template <typename T>
class collection {};

class Level {
 public:
  // TODO: Placeholder until we decide what type of collection class to use
  template <typename T>
  class collection {};
  collection<Wall*>& getWalls();

 private:
  // Owns walls, player, bullets from player, robots, and bullets from robots collection<Wall*> _walls;
  class LevelShootingProxy : public ShootingProxy {
   public:
    void shoot(const Direction& direction, const Vect2D& origin) const override;
  };
};
