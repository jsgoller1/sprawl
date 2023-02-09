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
  Otto(const Vect2D& position, DrawingProxy& drawingProxy, PlayerPositionProxy& playerPositionProxy,
       const OttoSpriteManager& ottoSpriteManager);
  void update(const TimerProxy& timerProxy);

  AnimatedDrawingComponent& getDrawingComponent() const override;
  void resolveCollision(GameObject& target) override;

 private:
  OttoState _state;
  std::unique_ptr<AnimatedDrawingComponent> _drawingComponent = nullptr;
  PlayerPositionProxy& _playerPositionProxy;

  const OttoSpriteManager& _ottoSpriteManager;
  std::unique_ptr<OttoAnimationSet> _ottoAnimationSet = nullptr;
};
