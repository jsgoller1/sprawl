
#pragma once

#include "AIComp.hh"
#include "CharacterPhysicsComponent.hh"
#include "CombatComp.hh"
#include "GameAction.hh"
#include "GameObject.hh"
#include "Logger.hh"
#include "Math.hh"
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

  // TOOD: Is there a way we can ensure all GameObject descendants have a
  // PhysicsComponent by default, but can override it with a child of
  // PhysicsComponent if they want without having to redeclare the attribute as
  // the new child type? Doing this feels dangerous, because we could
  // accidentally wind up with two physics components on an object (e.g. if I
  // subtly rename one). We do want GameObjects to have a PhysicsComp, so we
  // shouldn't move its declaration to the base class.
  shared_ptr<CharacterPhysicsComponent> physicsComp;

  bool canDoubleJump;
};

typedef shared_ptr<Character> CharacterSPtr;
