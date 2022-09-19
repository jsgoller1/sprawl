
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
  Character(const CharacterNameSPtr name, const FilePathSPtr texturePath,
            const PointSPtr center);
  void shoot();
  void move(const GameAction& action);
  void shoot(const GameAction& action);

 private:
  CharacterNameSPtr name;
  AICompSPtr aiCompSPtr;
  CombatCompSPtr combatCompSPtr;
};

typedef shared_ptr<Character> CharacterSPtr;
