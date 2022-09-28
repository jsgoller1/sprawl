
#pragma once

#include "AIComp.hh"
#include "CharacterPhysicsComponent.hh"
#include "CombatComp.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "Memory.hh"
#include "PositionComp.hh"
#include "Types.hh"

typedef int JumpCount;

class Character : public GameObject {
  // Self explanatory: parent class for player, npcs, enemies, etc
 public:
  Character(const shared_ptr<Vect2D> center,
            const GameObjectNameSPtr name = nullptr,
            const shared_ptr<CharacterPhysicsComponent> physicsComp = nullptr,
            const FilePathSPtr texturePath = nullptr,
            const DrawingCompSPtr drawingComp = nullptr);
  void shoot();
  void move(const GameAction& action);
  void shoot(const GameAction& action);
  void jump();

 private:
  AICompSPtr aiCompSPtr;
  CombatCompSPtr combatCompSPtr;
  shared_ptr<Vect2D> moveSpeed;
  JumpCount jumpCount;
};

typedef shared_ptr<Character> CharacterSPtr;
