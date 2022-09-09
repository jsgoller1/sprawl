
#pragma once

#include "AIComponent.hh"
#include "CombatComponent.hh"
#include "GameObject.hh"
#include "Memory.hh"
#include "Types.hh"

class Character : public GameObject {
  // Self explanatory: parent class for player, npcs, enemies, etc
 public:
  Character(const CharacterName& name);
  void shoot();

 private:
  CharacterNamePS name;
  shared_ptr<AIComponent> aiComponent;
  shared_ptr<CombatComponent> combatComponent;
};

typedef shared_ptr<Character> CharacterPS;
