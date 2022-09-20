
#pragma once

#include "AIComp.hh"
#include "CombatComp.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "Memory.hh"
#include "PositionComp.hh"
#include "Types.hh"

class Character : public GameObject {
  // Self explanatory: parent class for player, npcs, enemies, etc
 public:
  Character(const PointSPtr center, const GameObjectNameSPtr name = nullptr,
            const PhysicsCompSPtr physicsComp = nullptr,
            const FilePathSPtr texturePath = nullptr,
            const DrawingCompSPtr drawingComp = nullptr);
  void shoot();
  void move(const GameAction& action);
  void shoot(const GameAction& action);

 private:
  AICompSPtr aiCompSPtr;
  CombatCompSPtr combatCompSPtr;
};

typedef shared_ptr<Character> CharacterSPtr;
