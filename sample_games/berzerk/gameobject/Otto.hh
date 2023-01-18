#pragma once
#include "GameObject.hh"
#include "Time.hh"

class Otto : public GameObject {
 public:
  void update(const time_ms deltaT);
};
