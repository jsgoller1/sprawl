
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
            const DrawingCompSPtr drawingComp = nullptr,
            const PositionUnit maxSpeed = 0.0,
            const PositionUnit minSpeed = 0.0,
            const real dragCoefficient = 0.0);
  void shoot();
  void move(const GameAction& action);
  void shoot(const GameAction& action);
  void jump();

  // NOTE: Name hiding GameObject::getPhysicsComponent()
  // so we can have covariant return with shared pointers. See:
  // https://www.fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance/
  shared_ptr<CharacterPhysicsComponent> getPhysicsComponent() {
    return this->getRawPhysicsComponent()->getptr();
  }

 private:
  AICompSPtr aiCompSPtr;
  CombatCompSPtr combatCompSPtr;
  shared_ptr<CharacterPhysicsComponent> physicsComponent;

  void setPhysicsComponent(shared_ptr<CharacterPhysicsComponent> comp) {
    this->physicsComponent = comp;
  }

  CharacterPhysicsComponent* getRawPhysicsComponent() override {
    return this->physicsComponent.get();
  };

  bool canDoubleJump;
};

typedef shared_ptr<Character> CharacterSPtr;
