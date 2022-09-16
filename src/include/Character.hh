
#pragma once

#include "AIComp.hh"
#include "CombatComp.hh"
#include "GameObject.hh"
#include "Memory.hh"
#include "Types.hh"

class Character : public GameObject {
  // Self explanatory: parent class for player, npcs, enemies, etc
 public:
  Character(const CharacterName& name);
  void shoot();

 private:
  CharacterNameSPtr name;
  AICompSPtr aiCompSPtr;
  CombatCompSPtr combatCompSPtr;
};

typedef shared_ptr<Character> CharacterSPtr;
