#pragma once

#include "GameAction.hh"
#include "Memory.hh"

class CombatComp {
 public:
  void shoot(const GameAction& action);
};

typedef shared_ptr<CombatComp> CombatCompSPtr;
