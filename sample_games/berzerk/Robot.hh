#pragma once

#include "GameObject.hh"

class Robot : public GameObject {
 public:
  void aiBehavior(const Vect2D& playerPosition);

 private:
  // Has: heading direction
  // enum RobotState { IDLE, MOVING, SHOOTING, DYING, DEAD };
  // RobotState _state;

  Direction lineScan(const GameObject& target);
  void move();
};
