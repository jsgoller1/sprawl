#pragma once

#include "Memory.hh"

class PhysicsMgr {
  // Keeps track of registered PhyiscsComponents and knows how to apply physics
  // to them
 public:
  void applyGravity();
};

typedef unique_ptr<PhysicsMgr> PhysicsMgrSPtr;
