#pragma once

#include "AnimatedDrawingComponent.hh"
#include "GameObject.hh"
#include "OttoAnimationSet.hh"
#include "OttoSpriteManager.hh"
#include "PlayerPositionProxy.hh"
#include "State.hh"
#include "Time.hh"

class Otto : public GameObject {
 public:
  Otto(const int levelNo, const Vect2D& position, DrawingProxy& drawingProxy, PlayerPositionProxy& playerPositionProxy,
       OttoSpriteManager& ottoSpriteManager);
  void update(const TimerProxy& timerProxy);
  void draw();

  AnimatedDrawingComponent& getDrawingComponent() const override;
  void resolveCollision(GameObject& target) override;

 private:
  int _currentJumpVerticalOffsetCount = 0;
  time_ms _timeSinceLastVerticalMovement = 0;
  OttoState _state = OttoState::OUT_OF_PLAY;
  std::unique_ptr<AnimatedDrawingComponent> _drawingComponent = nullptr;
  PlayerPositionProxy& _playerPositionProxy;

  OttoSpriteManager& _ottoSpriteManager;
  std::unique_ptr<OttoAnimationSet> _ottoAnimationSet = nullptr;

  OttoState getNewState(const OttoState currentState, const TimerProxy& timerProxy);
  void stateBehaviorSpawning();
  void stateBehaviorChasing(const TimerProxy& timerProxy);
  void updateJumpDisplacement(const TimerProxy& timerProxy);
  void moveChasingPlayer();
};
